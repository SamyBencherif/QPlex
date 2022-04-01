from scene import *
import sound
import random
import math
A = Action

class MyScene (Scene):
	def setup(self):
		pass
	
	def did_change_size(self):
		pass
	
	def update(self):
		background(1,1,1)
		fill(0.74, 0.11, 1.)
		ellipse(100,self.size.h/2-100,200,200)
	
	def touch_began(self, touch):
		pass
	
	def touch_moved(self, touch):
		pass
	
	def touch_ended(self, touch):
		pass

if __name__ == '__main__':
	run(MyScene(), show_fps=False)
