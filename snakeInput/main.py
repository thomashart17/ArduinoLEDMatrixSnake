import pynput
import serial


class SerialInput:
    PORT = "COM5"

    def __init__(self):
        self.serial_port = serial.Serial(self.PORT, 9600)
        self.listener = pynput.keyboard.Listener(on_press=self.on_press)

    def start(self):
        self.listener.start()
        self.listener.join()

    def stop(self):
        self.listener.stop()

    def on_press(self, key):
        print(key)
        if key == pynput.keyboard.Key.esc:
            self.stop()
        elif key == pynput.keyboard.Key.enter:
            self.serial_port.write("0".encode())
        elif key == pynput.keyboard.Key.up:
            self.serial_port.write("1".encode())
        elif key == pynput.keyboard.Key.left:
            self.serial_port.write("2".encode())
        elif key == pynput.keyboard.Key.down:
            self.serial_port.write("3".encode())
        elif key == pynput.keyboard.Key.right:
            self.serial_port.write("4".encode())


def main():
    serial_input = SerialInput()
    serial_input.start()


if __name__ == '__main__':
    main()