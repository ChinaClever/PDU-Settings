from ctrlset_zpdu.zpdu_web import  *
import datetime

class Zpdu(ZpduWeb):
       
    def start_fun(self , sock , dest_ip , dest_port):
        cfg = self.cfgs
        self.sock = sock
        self.ip = dest_ip
        self.port = dest_port
        intRet , message = 0 , ''
        if(cfg['ip_prefix'] == 'https://'):
            intRet , message = self.login1()
            self.sendtoMainapp(message)
            if(intRet == 0):
                return
        intRet , message = self.login2()
        self.sendtoMainapp(message)
        if(intRet == 0):
            return
        
        intRet , message = self.changetocorrect()
        self.sendtoMainapp(message)
        if(intRet == 0):
            return
        self.setCorrect1()
        self.checkMacAddress()
             
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
            #if( self.checkId('//table[1]/tbody/tr[last()]/td[4]/input')==1 ):
            #    self.driver.find_element_by_xpath('//table[1]/tbody/tr[last()]/td[4]/input').click()
            #    time.sleep(0.35)
            time.sleep(3)
            self.execJs(cfg['setmaccontrolid'])
            time.sleep(1)
            #else:
            #    return 1
        else:
            self.sendtoMainapp('MAC-1')
        

    def checkId(self , id):
        try:
            it = self.driver.find_element_by_xpath(id)
        except NoSuchElementException:
            msg = '网页上找不到{0};1'.format(id)
            self.sendtoMainapp(msg)
            return 0
        else:
            return 1
    
    def checkCorrectHtml(self):
        cfg = self.cfgs
      
        if (len(cfg['mac']) > 5  ):
            status , message = self.macAddrCheck( cfg['maccontrolid'] , cfg['mac'] , 'mac地址')
            self.sendtoMainapp(message)
        
        self.driver.back()
        
    def checkMacAddress(self):
        cfg = self.cfgs
        try:
            self.driver.find_element_by_id(cfg['maccontrolid'])
        except NoSuchElementException:
            message = '检查MAC地址时，无法找到MAC控件;0'
            self.sendtoMainapp(message)
            time.sleep(0.35)
            return
        v = self.driver.find_element_by_id(cfg['maccontrolid']).get_attribute('value')
        if( '2C:26:5F:' not in v):
            message = 'MAC设置失败%s;0'%v
            self.sendtoMainapp(message)
        else:
            message = 'MAC设置成功%s;1'%v
            self.sendtoMainapp(message)