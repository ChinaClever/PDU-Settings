from ctrlset_rpdu.rpdu_web import  *
import datetime

class Rpdu(RpduWeb):
       
    def start_fun(self , sock , dest_ip , dest_port):
        cfg = self.cfgs
        self.ip_prefix = 'http://'
        self.sock = sock
        self.ip = dest_ip
        self.port = dest_port
        intRet , message = self.login()
        self.sendtoMainapp(message)
        if(intRet == 0):
            return
        
        time.sleep(1)
        self.changetocorrect()
        self.setCorrect1()
        #time.sleep(30)
        #self.login()
        #self.changetocorrect()
        #self.checkCorrectHtml()
        #self.driver.quit()
             
    def close(self):
        time.sleep(0.1)
        #print(datetime.datetime.now())
        self.driver.quit()
        print(datetime.datetime.now())
        time.sleep(3)
        

    def changetocorrect(self):
        cfg = self.cfgs
        ip = self.ip_prefix + cfg['ip_addr'] + '/debug.html'
        
        self.driver.get(ip)
        time.sleep(1)
        
        self.driver.switch_to.default_content()
    
    def setCorrect1(self):
        cfg = self.cfgs
        time.sleep(3) 
        if (len(cfg['mac']) > 5  ):#NoSuchElementException
            strMac =  cfg['mac']
        try:
            self.driver.find_element_by_id('mac')
        except NoSuchElementException:
            return
        v = self.driver.find_element_by_id('mac').get_attribute('value')
        if( '2C:26:5F:' not in v):
            v = strMac
            self.setItById("mac", cfg['mac'], 'Mac地址')
            self.execJs("savedebug()")
        else:
            self.sendtoMainapp('MAC-1')
               
        #time.sleep(1)
        #self.driver.back()
        #self.divClick(7)
        #time.sleep(0.5)
        
        #if( self.checkByXpath('/html/body/div[last()]/div[last()]/fieldset[last()]/input')==1 ):
        #    self.driver.find_element_by_xpath('/html/body/div[last()]/div[last()]/fieldset[last()]/input').click()
        #   time.sleep(0.15)
        #    self.driver.switch_to.alert.accept()
        #    time.sleep(2)
        #    self.driver.switch_to.alert.accept()
        #else:
        #    return

    def checkByXpath(self , path):
        try:
            it = self.driver.find_element_by_xpath(path)
        except NoSuchElementException:
            msg = '网页上找不到{0};1'.format(path)
            self.sendtoMainapp(msg)
            return 0
        else:
            return 1
    
    def checkById(self , id):
        try:
            it = self.driver.find_element_by_id(id)
        except NoSuchElementException:
            msg = '网页上找不到{0};1'.format(id)
            self.sendtoMainapp(msg)
            return 0
        else:
            return 1
    
    def checkCorrectHtml(self):
        cfg = self.cfgs
        time.sleep(2)
        
        if (len(cfg['mac']) > 5  ):
            status , message = self.macAddrCheck( 'mac' , cfg['mac'] , 'mac地址')
            self.sendtoMainapp(message)
        
        self.driver.back()
            