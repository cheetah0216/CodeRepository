"Python's garbage collector runs during program execution and is triggered when an object's reference count reaches zero."
"An object's reference count changes as the number of aliases that point to it changes."

"An object's reference count increases when it's assigned a new name or placed in a container (list, tuple or dictionary)."
"The object's reference count decreases when it's deleted with del, its reference is reassigned, or its reference goes out"
"of scope. When an object's reference count reaches zero, Python collects it automatically."

class Point:
   def __init( self, x=0, y=0):
      self.x = x
      self.y = y
   def __del__(self):
      class_name = self.__class__.__name__
      print class_name, "destroyed"

pt1 = Point()
pt2 = pt1
pt3 = pt1
print id(pt1), id(pt2), id(pt3) # prints the ids of the obejcts
del pt1
del pt2
del pt3
