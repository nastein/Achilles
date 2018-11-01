import numpy as np
from nuChic.FourVector import Vec4

class Particle:
    def __init__(self,pid=0,mom=Vec4(),charge=0,I3=0,status=0,mothers=None,daughters=None):
        self.pid = pid
        self.mom = mom
        self.charge = charge
        self.I3 = I3
        self.status = status
        self.mothers = mothers if mothers is not None else []
        self.daughters = daughters if daughters is not None else []

    def isFinal(self):
        if self.status == 1:
            return True
        return False

    def Px(self):
        return self.mom.px

    def Py(self):
        return self.mom.py

    def Pz(self):
        return self.mom.pz

    def E(self):
        return self.mom.E

    def M(self):
        return self.mom.M()
