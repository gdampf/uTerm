# The MIT License (MIT)
# 
#  Copyright (c) 2017 Madis Kaal <mast@nomad.ee>
# 
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
# 
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
# 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.

import curses
import traceback
import sys
import os

screen=None
font=[]
cell=[]
cx=0
cy=0
clip=None
filename=None

for i in range(0,16):
  cell.append(0)
  
for i in range(0,256):
  font.append(list(cell))
  
currentchar=ord('A')
markchar=None

def setfontheight(r):
  global font,cell,cy
  fontrows=len(cell)
  if r==fontrows:
    return
  if r<fontrows:
    for i in range(0,256):
      font[i]=font[i][:r]
    cell=cell[:r]
    cy=0
  else:
    for i in range(0,256):
      for j in range(0,r-fontrows):
        font[i].append(0)
    for j in range(0,r-fontrows):
      cell.append(0)
  clip=None
  markchar=None
  return
      
def load(file):
  global font,cell,currentchar,filename
  filename=file
  try:
    f=open(filename,"rb")
    data=f.read()
    f.close()
  except:
    return
  r=len(data)/256
  if r>0 and r<21:
    setfontheight(r)
    for c in range(0,256):
      for i in range(0,r):
        cell[i]=ord(data[c*r+i])
      font[c]=list(cell)
    cell=list(font[currentchar])
    
  return
  
def save():
  global cell,font,currentchar,filename
  font[currentchar]=list(cell)
  os.rename(filename,filename+"~")
  f=open(filename,"wb")
  for c in range(0,256):
    for r in range(0,len(cell)):
      f.write(chr(font[c][r]))
  f.close()
  return

def export():
  global cell,font,currentchar,filename
  font[currentchar]=list(cell)
  f=open(filename+".c","wt")
  f.write("  // %s\n"%filename)
  for c in range(0,256):
    f.write("  // 0x%02x"%c)
    if c>31 and c<127:
      f.write(" '%c'"%chr(c))
    f.write("\n  ")
    for r in range(0,len(cell)):
      f.write("0x%02x,"%font[c][r])
    f.write("\n");
  f.close()
  return
    
def redraw():
  global screen,currentchar
  for y in range(0,len(cell)):
    v=cell[y]
    screen.addstr(y+1,0,str((y+1)%10))
    for c in range(0,8):
      if v&0x80:
        screen.addstr(y+1,c*2+2,'  ',curses.A_REVERSE)
      else:
        screen.addch(y+1,c*2+2,curses.ACS_BULLET)
        screen.addch(y+1,c*2+3,curses.ACS_BULLET)
      v=v<<1
  screen.addstr(1,22,"%02x"%currentchar)
  if currentchar>31 and currentchar!=127 and currentchar!=255:
    screen.addstr(2,22,chr(currentchar))
  else:
    screen.addstr(2,22,"  ")
  for i in range(len(cell),21):
    screen.addstr(i+1,0,"                        ")
  screen.addstr(0,2,"1 2 3 4 5 6 7 8")
  screen.move(cy+1,cx*2+2)
  screen.refresh()        
  return

def help():
  global screen
  screen.addstr(2,40,"q - save and quit")
  screen.addstr(3,40,"Q - quit without saving")
  screen.addstr(4,40,"arrow keys - move cursor")
  screen.addstr(5,40,"pgup/< pgdn/> - prev/next character")
  screen.addstr(6,40,"space - flip dot")
  screen.addstr(7,40,"i - invert character/block")
  screen.addstr(8,40,"z - clear character")
  screen.addstr(9,40,"r/R - rotate down/up")
  screen.addstr(10,40,"")
  screen.addstr(11,40,"T - make characters taller")
  screen.addstr(12,40,"S - make characters shorter")
  screen.addstr(13,40,"")
  screen.addstr(14,40,"m - mark block start")
  screen.addstr(15,40,"c - copy character/block")
  screen.addstr(16,40,"p - paste character/block")
  screen.addstr(17,40,"")
  screen.addstr(18,40,"E - export C source")

def status(s):
  global screen
  screen.move(0,40)
  screen.clrtoeol()
  screen.addstr(0,40,s)
  
def editor(stdscr):
  global screen,cx,cy,currentchar,cell,clip,markchar
  screen=stdscr
  screen.clear()
  help()
  while 1:
    redraw()
    c=screen.getch()
    status("")
    if c==ord('q'):
      save()
      break
    if c==ord('Q'):
      break
    elif c==261: #right
      cx=(cx+1)%8
    elif c==258: #down
      cy=(cy+1)%len(cell)
    elif c==259: #up
      cy=(cy-1)%len(cell)
    elif c==260: #left
      cx=(cx-1)%8
    elif c==338 or c==ord('>'): #pgdn
      font[currentchar]=list(cell)
      currentchar=(currentchar+1)%256
      cell=list(font[currentchar])
    elif c==339 or c==ord('<'): #pgup
      font[currentchar]=list(cell)
      currentchar=(currentchar-1)%256
      cell=list(font[currentchar])
    elif c==ord('i'):
      font[currentchar]=list(cell)
      if markchar==None:
        markchar=currentchar
      if markchar<currentchar:
        b=markchar
        e=currentchar
      else:
        b=currentchar
        e=markchar
      for i in range(b,e+1):
        for r in range(0,len(cell)):
          font[i][r]=font[i][r]^0xff 
      cell=list(font[currentchar])
      status("Inverted %d characters"%(e+1-b))
      markchar=None
    elif c==ord('z'):
      for i in range(0,len(cell)):
        cell[i]=0
    elif c==ord('m'):
      markchar=currentchar
      status("Mark placed")
    elif c==ord('c'):
      font[currentchar]=list(cell)
      clip=[]
      if markchar==None:
        markchar=currentchar
      if markchar<currentchar:
        b=markchar
        e=currentchar
      else:
        b=currentchar
        e=markchar
      for i in range(b,e+1):
        clip.append(list(font[i]))
      status("Copied %d characters"%len(clip))
      markchar=None
    elif c==ord('p'):
      b=currentchar
      for e in clip:
        font[b]=e
        b=(b+1)%256
      cell=list(clip[0])
      status("Pasted %d characters"%len(clip))
    elif c==ord('R'):
      cell.append(cell.pop(0))
    elif c==ord('r'):
      cell.insert(0,cell.pop())
    elif c==ord('T'):
      if len(cell)<20:
        setfontheight(len(cell)+1)
    elif c==ord('S'):
      if len(cell)>1:
        setfontheight(len(cell)-1)
    elif c==ord('E'):
      export()
      status("Font exported")
    elif c==ord(' '):
      v=cell[cy]
      v=v^(0x80>>cx)
      cell[cy]=v
    else:
      status("Unhandled key %s"%(str(c)))
  return

if len(sys.argv)>1:
  load(sys.argv[1])
  curses.wrapper(editor)
else:
  print "Usage: pythong fontedit.py <fontfile>"
