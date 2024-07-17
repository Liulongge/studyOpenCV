# # # -*- coding: UTF-8 -*-
 
# # from pynput.mouse import Listener
# # from tkinter import *
# # import tkinter as tk
 
# # global btstate
# # global btstate1
 
# # def on_hover():
# # 	global btstate
# # 	print("mouse over")
# # 	btstate=1
	
# # def on_leave():
# # 	global btstate
# # 	print("mouse leave")
# # 	btstate=0
 
# # def on_hover1():
# # 	global btstate1
# # 	print("mouse over")
# # 	btstate1=1
	
# # def on_leave1():
# # 	global btstate1
# # 	print("mouse leave")
# # 	btstate1=0
	
# # def callback(event):
# #     x = event.x
# #     y = event.y
# #     textvar= "移动位置-x:{},y:{}".format(x,y)
# #     var.set(textvar)
 
# # def on_click(x, y, button, is_press):
# # 	global btstate
# # 	global btstate1
# # 	# print(f"鼠标{button}键在({x}, {y})处{'按下' if is_press else '松开'}")
# # 	if is_press and btstate==1:
# # 		print("press button1!")
# # 	elif  btstate==1:
# # 		print("release button1!")
		
# # 	if is_press and btstate1==1:
# # 		print("press button2!")
# # 	elif  btstate1==1:
# # 		print("release button2!")
		
 
# # root = Tk()
# # root.title("tk鼠标按下和弹起事件")
# # root.geometry("400x300")
 
 
# # B = tk.Button(root, text ="点我")
# # B.pack()
# # B.bind('<Enter>',lambda event :on_hover())
# # B.bind('<Leave>',lambda event :on_leave())
 
# # C = tk.Button(root, text ="点我")
# # C.pack()
# # C.bind('<Enter>',lambda event :on_hover1())
# # C.bind('<Leave>',lambda event :on_leave1())
 
# # listener = Listener(on_click=on_click)
# # listener.start()
 
# # x,y=0,0
# # var = StringVar()
# # text = "移动位置-x:{},y:{}".format(x,y)
# # var.set(text)
 
# # lab = Label(root,textvariable=var)
# # lab.pack(anchor=S,side=RIGHT,padx=10,pady=10)
# # root.bind("<Motion>",callback)
 
# # root.mainloop()


# from pynput.mouse import Listener

# # This function will be called when any key of mouse is pressed
# def on_click(*args):
#     # see what argument is passed.
#     print(args)
#     if args[-1]:
#         # Do something when the mouse key is pressed.
#         print('The "{}" mouse key has held down'.format(args[-2].name))

#     elif not args[-1]:
#         # Do something when the mouse key is released.
#         print('The "{}" mouse key is released'.format(args[-2].name))

# # Open Listener for mouse key presses
# with Listener(on_click=on_click) as listener:
#     # Listen to the mouse key presses
#     listener.join()

# import pip, os, time

# for package in pip.get_installed_distributions():
#      print(package, time.ctime(os.path.getctime(package.location)))

import pip
from subprocess import call
from importlib import metadata as importlib_metadata
# 上一条语句在低版本中可能要改成 import importlib_metadata
for dist in importlib_metadata.distributions():
    print("Updating for:", dist.metadata["Name"])  # 看进度用，非必需
    call("pip install -U " + dist.metadata["Name"], shell=True)
