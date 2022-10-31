from abc import ABC, abstractmethod

class MyTrait(ABC):
    def __init__(self):
        pass

    @abstractmethod
    def foo(self):
        """A required method for this class"""
        pass

class MyOtherTrait(ABC):
    def __init__(self):
        pass

    @abstractmethod
    def baz(self):
        """A required method for this class"""
        pass

class MyType(MyTrait, MyOtherTrait):
    def __init__(self, attribute):
        self.attribute = attribute

    def bar(self):
        print("I'm a default implementation defined on this type.")

    def bar(self):
        print("I'm a required method for the MyTrait class.")

    def baz(self):
        print("I'm a required method for the MyTrait class.")


def main ():
    mytype = MyType("boz")

    # Use behaviour from MyTrait
    print(mytype.foo())
    
    # Use behaviour from MyOtherTrait
    print(mytype.baz())

    # Use behaviour defined by MyType itself
    print(mytype.bar())
    

