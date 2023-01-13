from selenium import webdriver
from selenium.webdriver.support.select import Select
from selenium.common.exceptions import NoSuchElementException
from selenium.common.exceptions import UnexpectedAlertPresentException
from selenium.common.exceptions import WebDriverException
import configparser
import time
import os

class ZpduWeb:

    def __init__(self):
        self.initCfg()
        self.initDriver()

    def initDriver(self):
        try:
            self.driver = webdriver.Firefox(executable_path="geckodriver.exe")
        except ValueError:
            self.driver = webdriver.Chrome(executable_path="chromedriver.exe")

    @staticmethod
    def getCfg():
        cf = configparser.ConfigParser()
        fn = os.path.expanduser('~') + "/.PDU-Settings/cfg.ini"
        cf.read(fn, 'utf-8-sig')  # 读取配置文件，如果写文件的绝对路径，就可以不用os模块
        return cf

    def initCfg(self):
        
        self.cfgs = {'versions':'','ip_prefix':'http://','user': 'admin', 'password': 'admin',
                     'ip_addr': '192.168.1.163', 'backendaddress':  './debug.html',
                     'maccontrolid':  'mac','setmaccontrolid':  'setdebug()','mac':''}
        items = ZpduWeb.getCfg().items("zpduCfg")  # 获取section名为Mysql-Database所对应的全部键值对
        self.cfgs['mac'] = ZpduWeb.getCfg().get("Mac", "mac")
        for it in items:
            self.cfgs[it[0]] = it[1]

    def login1(self):
        ip =  self.cfgs['ip_prefix'] +self.cfgs['ip_addr']
        try:
            self.driver.get(ip)
        except WebDriverException:
            return 0,'输入IP错误;0'
        
        self.login(self.cfgs['user'] , 'admin')
        win = self.driver.switch_to_alert()
        print(win.text)
        if( '错误' in win.text):
            win.accept()
            return 1,'账号和密码错误;1'
        win.send_keys(self.cfgs['password'])
        win.accept()
        time.sleep(2)
        win = self.driver.switch_to_alert()
        win.send_keys(self.cfgs['password'])
        win.accept()
        self.driver.refresh()
        time.sleep(2)
        return 1,'输入IP正确;1'
        
    def login2(self):
        ip =  self.cfgs['ip_prefix'] +self.cfgs['ip_addr']
        try:
            self.driver.get(ip)
        except WebDriverException:
            return 0,'输入IP错误;0'
        self.login(self.cfgs['user'] , self.cfgs['password'])
        try:
            win = self.driver.switch_to_alert()
            print(win.text)
            if( '错误' in win.text):
                win.accept()
                return 0,'再次输入账号和密码错误;0'
        except:
            time.sleep(2)
            return 1,'输入IP正确;1'
    
    def login(self , user , password ):    
        self.setItById('name', user , '账号')
        self.setItById('psd', password  , '密码')
        self.execJs('login()')
        
    def setEle(self):
        self.divClick(3)
        jsSheet = " claerset = createXmlRequest();claerset.onreadystatechange = clearrec;ajaxget(claerset, \"/energyzero?a=\" + {0}+\"&\");"        
        for num in range(0, 4):
            self.execJs(jsSheet.format(num))

    def setSelect(self, id, v):
        it = self.driver.find_element_by_id(id)
        if it.is_displayed():
            Select(it).select_by_index(v)
            time.sleep(1)

    

    def btnClick(self, id):
        try:
            self.driver.find_element_by_id(id).click()
            time.sleep(0.5)
        except:
            msg = '网页上找不到{0}'.format(id)
            self.sendtoMainapp(msg, 0)

    def alertClick(self, id):
        try:
            self.btnClick(id)
            self.driver.switch_to.alert.accept()
            time.sleep(0.35)
        except:
            msg = '网页上没有弹框'

    def divClick(self, id):
        self.driver.switch_to.default_content()
        self.execJs("clk({0})".format(id))
        self.driver.switch_to.frame('rightMain')

    def execJs(self, js):
        try:
            self.driver.execute_script(js)
            time.sleep(0.35)
        except:
            return

    def execJsAlert(self, js):
        self.execJs(js)
        self.driver.switch_to.alert.accept()
        time.sleep(0.5)
        
    def check(self, ssid , value , parameter):
        try:
            message =''
            self.driver.find_element_by_id(ssid)
        except NoSuchElementException:
            message =  '网页上找不到{0}ID;'.format(parameter)+str(2)
            sock.sendto(message.encode('utf-8-sig') , (dest_ip , dest_port))
            return 2,message
        v = self.driver.find_element_by_id(ssid).get_attribute('value')
        #print(type(v))
        ret = 1
        if( value != self.driver.find_element_by_id(ssid).get_attribute('value') ):
            message = '设置{0}失败，实际值{1}，期待值{2};'.format(parameter,v,value)+str(0)
            ret = 0
        else:
            message ='设置{0}成功{1};'.format(parameter,value)+str(1)
        #sock.sendto(message.encode('utf-8-sig') , (dest_ip , dest_port))
        return ret,message
            
    def checkStr(self, ssid , value , parameter):
        try:
            message =''
            self.driver.find_element_by_id(ssid)
        except NoSuchElementException:
            message =  '网页上找不到{0}ID;'.format(parameter)+str(2)
            #sock.sendto(message.encode('utf-8-sig') , (dest_ip , dest_port))
            return 2,message
        v = self.driver.find_element_by_id(ssid).get_attribute('value')
        if ( isinstance(v,int)):
            v = str(v)
        ret = 1
        if( value == v ):
            message ='设置{0}成功{1};'.format(parameter,value)+str(1)
        else:
            message = '设置{0}失败，实际值{1}，期待值{2};'.format(parameter,v,value)+str(0)
            ret = 0
        #sock.sendto(message.encode('utf-8-sig') , (dest_ip , dest_port))
        return ret,message
        
    def sendtoMainapp(self, parameter):
        sock = self.sock
        dest_ip = self.ip
        dest_port = self.port
        message = parameter
        sock.sendto(message.encode('utf-8-sig') , (dest_ip , dest_port))
        
    def checkVersion(self):
        cfg = self.cfgs
        try:
            self.divClick(1)
            message = '登陆成功;1'
            self.sendtoMainapp(message)
            time.sleep(5)
            tt = self.driver.find_element_by_xpath('//table[2]/tbody/tr[2]/td[2]')
            #print(tt.text)
            if( cfg['versions'] == ''):
                return 2,'软件版本空;2'
                
            if( cfg['versions'] in tt.text and len(str(cfg['versions'])) >= 2 ):
                return 1,'软件版本正确;1'
            else:
                return 0,'软件版本错误;0'
        except UnexpectedAlertPresentException:
            message = '登陆失败，账号密码错误;0'
            return 0,message
            
    def macAddrCheck(self , ssid , value , parameter):
        cfg = self.cfgs
        try:
            message =''
            self.driver.find_element_by_id(ssid)
        except NoSuchElementException:
            message =  '网页上找不到{0}ID;'.format(parameter)+str(2)
            #sock.sendto(message.encode('utf-8-sig') , (dest_ip , dest_port))
            return 2,message
        v = self.driver.find_element_by_id(ssid).get_attribute('value')
        ret = 1
        if( v == cfg['mac']):
            message ='设置{0}成功{1};'.format(parameter,value)+str(1)
        else:
            message = '没有设置{0}，实际值{1}，当前值{2};'.format(parameter,v,cfg['mac'])+str(1)
        #sock.sendto(message.encode('utf-8-sig') , (dest_ip , dest_port))
        return ret,message
        
    def setItById(self, id, v, parameter):
        try:
            it = self.driver.find_element_by_id(id)
        except NoSuchElementException:
            msg = '网页上找不到{0}'.format(id)
            #self.sendtoMainapp(msg, 0)
        else:
            it.clear()
            it.send_keys(str(v))
            msg = '设置{0} {1}：{2};1'.format(parameter, id, v)
            self.sendtoMainapp(msg)




