class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError("Invalid capacity!")
        else:
            self._capacity = capacity
            self._size = 0

    def __str__(self):
        return ("🍪" * self.size)

    def deposit(self, n):
        if (n + self.size) > self.capacity:
            raise ValueError("Capacity exceeded!")
        else:
            self._size += n


    def withdraw(self, n):
        if n > self.capacity:
            raise ValueError("Withdrawal exceeds size!")
        else:
            self._size -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

def main():
    jar = Jar()
    print("Capacity:")
    print(str(jar.capacity))

    print("Inside the Jar:")
    print(str(jar))

    jar.deposit(2)

    print("Inside the Jar after adding two cookies:")
    print(str(jar))

    jar.withdraw(1)

    print("Inside the Jar after withdrawing a cookie:")
    print(str(jar))


main()