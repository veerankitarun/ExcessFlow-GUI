import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from Utils.logger import Logger

logger = Logger("MainWindow")

def window():
   app = QApplication(sys.argv)
   w = QWidget()
   b = QLabel(w)
   b.setText("Hello World!")
   w.setGeometry(700,300,500,500)
   b.move(50,20)
   w.setWindowTitle("ExcessFlow App")
   w.show()
   sys.exit(app.exec_())
if __name__ == '__main__':
   window()