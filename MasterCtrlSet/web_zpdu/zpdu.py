from ctrlset_zpdu.zpdu_web import  *
import datetime

class Zpdu(ZpduWeb):
       
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
        
        self.changetocorrect()
        self.setCorrect1()
        time.sleep(50)
        self.login()
        self.changetocorrect()
        self.checkCorrectHtml()
             
    def close(self):
        time.sleep(1.5)
        #print(datetime.datetime.now())
        self.driver.quit()
        

    def changetocorrect(self):
        cfg = self.cfgs
        ip = self.ip_prefix + cfg['ip_addr'] + '/debug.html'
        
        self.driver.get(ip)
        time.sleep(1)
        
        self.driver.switch_to.default_content()
    
    def setCorrect1(self):
        cfg = self.cfgs
       
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
        else:
            self.sendtoMainapp('MAC-1')
        if( self.checkId('//table[1]/tbody/tr[last()]/td[4]/input')==1 ):
            self.driver.find_element_by_xpath('//table[1]/tbody/tr[last()]/td[4]/input').click()
            time.sleep(0.35)
            self.driver.back()
            if( self.checkId('/html/body/div/div/div[1]/ul/li[last()]')==1 ):
                self.driver.find_element_by_xpath('/html/body/div/div/div[1]/ul/li[last()]').click()
                time.sleep(0.15)
                if( self.checkId('/html/body/div/div/div[1]/ul/li[last()]/ul/li[last()]')==1 ):
                    self.driver.find_element_by_xpath('/html/body/div/div/div[1]/ul/li[last()]/ul/li[last()]').click()
                    time.sleep(0.5)
                    self.driver.switch_to.frame('iframe7_b')
                    if( self.checkId('/html/body/div/div/div[last()]/table/tbody/tr[last()]/td[2]/input')==1 ):
                        self.driver.find_element_by_xpath('/html/body/div/div/div[last()]/table/tbody/tr[last()]/td[2]/input').click()
                        time.sleep(0.15)
                        self.driver.switch_to.alert.accept()
                    else:
                        return
                else:
                    return
            else:
                return
        else:
            return

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
            status , message = self.macAddrCheck( 'mac' , cfg['mac'] , 'mac地址')
            self.sendtoMainapp(message)
        
        self.driver.back()
            