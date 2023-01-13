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
        intRet , message = self.changetocorrect()
        self.sendtoMainapp(message)
        if(intRet == 0):
            return
        self.setCorrect1()
             
    def close(self):
        time.sleep(5)
        #print(datetime.datetime.now())
        self.driver.quit()
        #print(datetime.datetime.now())
        time.sleep(3)
        

    def changetocorrect(self):
        cfg = self.cfgs
        ip = cfg['ip_prefix'] + cfg['ip_addr'] + cfg['backendaddress']
        
        try:
            self.driver.get(ip)
        except:
            self.sendtoMainapp('MAC-1')
            return 0,'账号密码错误;0'
        else:
            time.sleep(1)
            self.driver.switch_to.default_content()
            return 1,'账号密码正确;1'
    
    def setCorrect1(self):
        cfg = self.cfgs
        time.sleep(3) 
        if (len(cfg['mac']) > 5  ):#NoSuchElementException
            strMac =  cfg['mac']
        try:
            self.driver.find_element_by_id(cfg['maccontrolid'])
        except NoSuchElementException:
            message = '无法找到MAC控件;0'
            self.sendtoMainapp(message)
            time.sleep(0.35)
            self.sendtoMainapp('MAC-1')
        v = self.driver.find_element_by_id(cfg['maccontrolid']).get_attribute('value')
        if( '2C:26:5F:' not in v):
            v = strMac
            self.setItById(cfg['maccontrolid'], cfg['mac'], 'Mac地址')
            self.execJs(cfg['setmaccontrolid'])
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
            