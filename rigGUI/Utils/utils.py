import re
import os
import time
from datetime import datetime
from Utils.logger import Logger
from Utils.ConfigFile import ConfigFile
from Utils.TestData import TestData

logger = Logger("utils")

folder_name = ''

def checkAfcPstnSerial(afcPstnSerial:str, afcPstn:int)->bool:
    '''
    Verifies the scanned AFC position serial.
    Checks that it also matches the actual position
    '''
    logger.debug(f"Scanned afc position serial: {afcPstnSerial}")
    # Check the pattern of the serial number
    if re.search(ConfigFile.getValue("afc_position_regex"), afcPstnSerial):
        logger.info("Valid afc position serial")
        # Check that the position matches:
        if int(afcPstnSerial[-1]) == afcPstn:
            logger.info(f"Afc position {afcPstnSerial[-1]} matches expected position {afcPstn}")
            return True
        else:
            logger.debug(f"Afc position {afcPstnSerial[-1]} does not match expected position {afcPstn}")
            return False
    else:
        logger.error("Invalid afc position serial")
        return False
    
def checkAfcSerial(afcSerial:str, afcPstn:int)->bool:
    '''
    Verifies the scanned AFC position serial.
    Checks that it also matches the actual position
    '''
    logger.debug(f"Scanned afc position serial: {afcSerial}")
    # Check the pattern of the serial number
    for pattern in ConfigFile.getValue("afc_serial_regex"):
        if re.search(pattern, afcSerial):
            logger.info("Valid afc serial")
            # TO DO: Assign AFC Serial to position given
            # Check that the serial no is not repeated
            if afcSerial in TestData.ser_no.values():
                logger.warning("Afc serial already scanned")
                return False
            else:
                # save serial number 
                TestData.saveSerNo(f"POS{afcPstn}", afcSerial)
                return True
    else:
        logger.error("Invalid afc serial number")
        return False
    
def getTime():
    val = {}
    val['timestamp'] = time.time()
    _datetime = datetime.now()
    val['date'] = _datetime.strftime("%m-%d-%Y")
    val['time'] = _datetime.strftime("%H:%M:%S")

    return val

def createDirectory():
    '''
    Creates directories to ave test results
    '''
    try:
        logger.debug("Attempting to create folder path...")
        _date = datetime.now().strftime("%d%b%y").upper()
        folder_path = os.path.join("AFC_IQC_Results", _date)
        os.makedirs(folder_path, exist_ok=True)
        TestData.saveFolderPath(folder_path)
    except Exception as e:
        logger.error(f"Unabe to create directory: {e}")

