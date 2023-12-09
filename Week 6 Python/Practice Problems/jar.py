# I have chosen to use 'jar_size' and 'jar_capacity' to avoid the name clash with, e.g.:
#  @property
#   def capacity(self):
# because I didn't want to have to resort to using setters in this class, e.g.:
#   @capacity.setter
#     def capacity(self, capacity):
#         if capacity < 1:
#             raise ValueError("@capacity.setter error")
#         self._capacity = capacity
# Using a setter provides the obvious benefit of being able to have in the constructor something simple like:
#   self.capacity = capacity
#   self.size = 0
# Though this would have been better in some ways, it's not the focus of what was being practised here


class Jar:
    def __init__(self, capacity=12):
        self.jar_size = 0
        if capacity > 0:
            self.jar_capacity = capacity
        else:
            raise ValueError

    def __str__(self):
        if self.jar_size == 0:
            return "Oh no! No 🍪 in the jar!"
        else:
            return "🍪" * self.jar_size

    def deposit(self, n):
        if self.jar_size + n > self.jar_capacity:
            raise ValueError
        else:
            self.jar_size += n

    def withdraw(self, n):
        if self.jar_size - n < 0:
            raise ValueError
        else:
            self.jar_size -= n

    @property
    def capacity(self):
        return self.jar_capacity

    @property
    def size(self):
        return self.jar_size


def main():
    jar = Jar()
    print(str(jar.capacity))
    print(str(jar))
    jar.deposit(2)
    print(str(jar))
    jar.withdraw(1)
    print(str(jar))


if __name__ == "__main__":
    main()
