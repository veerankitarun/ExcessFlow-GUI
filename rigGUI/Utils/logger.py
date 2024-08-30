import logging

DATEFMT = "%H:%M:%S"
FORMAT = "%(asctime)s - %(levelname)s - %(name)s :: %(message)s"
DEBUG_LEVEL = logging.DEBUG

class ColorFormatter(logging.Formatter):
    COLORS = {
        'DEBUG': '\033[97m',  # Blue
        'INFO': '\033[92m',   # Cyan
        'WARNING': '\033[93m',  # Yellow
        'ERROR': '\033[91m',  # Red
        'CRITICAL': '\033[95m',  # Magenta
    }
    RESET = '\033[0m'

    @classmethod
    def change_color(cls,key,value):
        '''
        Changes the color of the given COLORS key
        '''
        cls.COLORS[key] = value

    def __init__(self, fmt=None, datefmt=None):
        super().__init__(fmt, datefmt)
        self._fmt = fmt
        self.datefmt = datefmt

    def format(self, record):
        log_fmt = self.COLORS.get(record.levelname, self.RESET) + self._fmt + self.RESET
        formatter = logging.Formatter(log_fmt, datefmt=self.datefmt)
        return formatter.format(record)
    
def Logger(name:str):
    # Define your logger
    logger = logging.getLogger(name)
    # Set the debug level to DEBUG
    logger.setLevel(DEBUG_LEVEL)

    # Check if handlers exist, if so , remove them
    if logger.hasHandlers():
        logger.handlers.clear()
    
    # Create the handlers
    logger = create_handlers(logger)

    return logger

def create_handlers(logger):
    '''
    Creates stream for the logger
    '''
    # Define the Stream handler
    console_handler = logging.StreamHandler()

    console_handler.setLevel(DEBUG_LEVEL)

    formatter = ColorFormatter(FORMAT, datefmt=DATEFMT)
    console_handler.setFormatter(formatter)

    logger.addHandler(console_handler)

    return logger

def startAppMessage(msg:str):
    LOGFORMAT = "%(asctime)s :: %(message)s"
    formatter = ColorFormatter(LOGFORMAT, datefmt=DATEFMT)
    formatter.change_color('INFO','\033[96m')
    stream = logging.StreamHandler()
    stream.setLevel(logging.INFO)
    stream.setFormatter(formatter)
    logger = logging.getLogger("Application start")
    logger.setLevel(logging.INFO)
    logger.addHandler(stream)
    logger.info(msg)
    formatter.change_color('INFO','\033[92m')

def setModuleLoggingLevel():
    # logging.getLogger("pyftdi.i2c").setLevel(logging.ERROR)
    # logging.getLogger("urllib3").setLevel(logging.ERROR)
    # logging.getLogger("bleak").setLevel(logging.ERROR)
    pass
