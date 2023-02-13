from ctrlset_ats.ats_web import  *
import datetime

class Ats(AtsWeb):
       
    def start_fun(self , sock , dest_ip , dest_port):
        cfg = self.cfgs
        self.sock = sock
        self.ip = dest_ip
        self.port = dest_port
        intRet = self.login()
        if(intRet == False):
            return
        
        intRet , message = self.changetocorrect()
        self.sendtoMainapp(message)
        if(intRet == 0):
            return
        self.setCorrect1()
             
    def close(self):
        time.sleep(0.1)
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
        time.sleep(2) 
        if (len(cfg['mac']) > 5  ):#NoSuchElementException
            strMac =  cfg['mac']
        try:
            self.driver.find_element_by_id(cfg['maccontrolid'])
        except NoSuchElementException:
            message = '无法找到MAC控件;0'
            self.sendtoMainapp(message)
            time.sleep(0.35)
            self.sendtoMainapp('MAC-1')
            return 0
        v = self.driver.find_element_by_id(cfg['maccontrolid']).get_attribute('value')
        if( '2C:26:5F:' not in v):
            v = strMac
            self.setItById(cfg['maccontrolid'], cfg['mac'], 'Mac地址')
            
            self.execJs(cfg['setmaccontrolid'])
            time.sleep(2)
            self.driver.switch_to.alert.accept()
            
            
        else:
            self.sendtoMainapp('MAC-1')
        
        #time.sleep(0.35)
        #self.driver.back()
        #self.divClick(9)
        #self.execJs("setdevice()")
        #time.sleep(0.5)
        #self.driver.switch_to.alert.accept()
    
    def checkCorrectHtml(self):
        cfg = self.cfgs
        time.sleep(2)
        
        if (len(cfg['mac']) > 5  ):
            status , message = self.macAddrCheck( 'mac' , cfg['mac'] , 'mac地址')
            self.sendtoMainapp(message)
        
        self.driver.back()
            