
from typing import Self
import math
class BasePhi:
    def run_rules(self, i) -> bool:
        if i == 0 and self.digits[i] >= 1 and self.digits[i + 1] >= 1:
            c = min(self.digits[i], self.digits[i+1])
            self.digits.insert(0, 0)
            self.dotIndex += 1
            self.digits[i] += max(c//2, 1)
            self.digits[i+1] -= max(c//2, 1)
            self.digits[i+2] -= max(c//2, 1)
            return True
        if self.digits[i + 1] >= 1 and self.digits[i + 2] >= 1:
            c = min(self.digits[i+1], self.digits[i+2])
            self.digits[i] += max(c//2, 1)
            self.digits[i+1] -= max(c//2, 1)
            self.digits[i+2] -= max(c//2, 1)
            return True
        if self.digits[i] >= 5:
            c = math.floor(self.digits[i]*0.40)
            self.digits[i+0] -= c
            self.digits[i+1] += c
            self.digits[i+2] += c
            return True
        if self.digits[i] >= 2:
            self.digits[i+0] -= 1
            self.digits[i+1] += 1
            self.digits[i+2] += 1
            return True

        return False

    def simplify(self, f = None) -> Self:

        if len(self.digits) == 1:
            if self.digits[0] == 0 or self.digits[0] == 1:
                return self

        changed = True
        while changed:
            if self.digits[-1] > 1:
                self.digits.append(0)
                self.digits.append(0)
            elif self.digits[-2] > 1:
                self.digits.append(0)

            if f is not None: print(self, end= " -> ")
            if f is not None and f != 1: f.write(self.__str__() + " -> ")

            for i in range(0, len(self.digits) - 2):
                changed = self.run_rules(i)
                if changed: break

            if f is not None and f != 1: f.write(self.__str__() + "\n")
            if f is not None: print(self)

        while self.digits[-1] == 0 and len(self.digits) > self.dotIndex:
            self.digits.pop()
        while self.digits[0] == 0 and self.dotIndex > 0:
            self.digits.pop(0)
            self.dotIndex -= 1
        return self

    def __str__(self):
        st = ""

        for i in range(0, self.dotIndex):
            if self.digits[i] > 9:
                st += "[" + str(self.digits[i]) + "]"
            else :
                st += str(self.digits[i])

        if len(self.digits) > self.dotIndex:
            st += "."
            for i in range(self.dotIndex, len(self.digits)):
                if self.digits[i] > 9:
                    st += "[" + str(self.digits[i]) + "]"
                else:
                    st += str(self.digits[i])
        return st
