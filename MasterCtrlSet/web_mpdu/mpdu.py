from setMonitor.mpdu_web import  *

class Mpdu(MpduWeb):

    def start_fun(self , sock , dest_ip , dest_port):
        self.ip_prefix = 'http://'
        self.sock = sock
        self.ip = dest_ip
        self.port = dest_port
        ret = self.login()
        if(ret == False):
            return
        ret = self.changetocorrect()
        if(ret == False):
            return
        self.setCorrect2()
        self.setCorrect1()
        time.sleep(5)
        self.login()
        self.changetocorrect()
        self.checkCorrectHtml()
        self.checkTitleBar2()
        self.checkTitleBar3()
        
    def setTime(self):
        self.divClick(8)
        self.execJsAlert("check_time()")

    def clearLogs(self):
        self.setTime()
        self.divClick(9)
        jsSheet = "xmlset = createXmlRequest();xmlset.onreadystatechange = setdata;ajaxgets(xmlset, \"/setlclear?a=\" + {0} + \"&\");"
        for num in range(0, 2):
            self.setSelect("loglist", num)
            self.execJs(jsSheet.format(num))
            time.sleep(1)
            
    def close(self):
        self.driver.close()

    def changetocorrect(self):
        cfg = self.cfgs
        ip = self.ip_prefix + cfg['ip_addr'] + '/correct.html'
        try:
            self.driver.get(ip)
            time.sleep(1)
        except UnexpectedAlertPresentException:
            message = '登陆失败，账号密码错误;0'
            self.sock.sendto(message.encode('gbk') , (self.ip , self.port))
            return False
        message = '登陆成功;1'
        self.sock.sendto(message.encode('gbk') , (self.ip , self.port))
        self.driver.switch_to.default_content()
        return True
        
    
    def setCorrect1(self):
        cfg = self.cfgs
        #self.setItById("LineN", cfg['lines'])
        #self.setItById("CircuitN", cfg['loops'])
        #self.setItById("OutputN", cfg['outputs'])
        #self.setItById("neutral", cfg['standar'])
        #self.setItById("type", cfg['series'])
        #self.setItById("language", cfg['language'])
        #self.setItById("breaker", cfg['breaker'])
        #self.setItById("serial", cfg['modbus'])
        if (len(cfg['mac']) > 5  ):#NoSuchElementException
            strMac =  cfg['mac']
        try:
            self.driver.find_element_by_id('mac1')
        except NoSuchElementException:
            return
        v = self.driver.find_element_by_id('mac1').get_attribute('value')
        if( (v == '' or v == 'FF:FF:FF:FF:FF:FF' or v == 'ff:ff:ff:ff:ff:ff') and len(cfg['mac']) > 5):
            v = strMac
        jsSheet1 = 'var level = document.getElementById("level").value;var claerset = createXmlRequest();claerset.onreadystatechange = setmac;ajaxget(claerset, \"/correct?a=\" +{set} +\"&b=\"+{type} +\"&c=\"+{language} + \"&d=\"+\"{mac1}\" + \"&e=\"+{breaker} + \"&f=\"+ {serial} + \"&g=\"+ {neutral}+\"&h=\"+{LineN}+\"&i=\"+{CircuitN} + \"&j=\"+{OutputN} + \"&k=\"+{level} +\"&\");'.format(set=int(1),type = cfg['series'] , language = cfg['language'] , mac1 = v , breaker = cfg['breaker'] , serial = cfg['modbus'] , neutral = cfg['standar'] , LineN = cfg['lines'] , CircuitN = cfg['loops'] , OutputN = cfg['outputs'] , level = str(0))
        #print(jsSheet1)
        self.execJs(jsSheet1)
        time.sleep(5)

    def setCorrect2(self):
        cfg = self.cfgs
        #self.setItById("Tvmin", cfg['vol_min'])
        #self.setItById("Tvmax", cfg['vol_max'])
        #self.setItById("Tcmin", cfg['cur_min'])
        #self.setItById("Tcxmin", cfg['cur_crmin'])
        #self.setItById("Tcxmax", cfg['cur_crmax'])
        #self.setItById("Tcmax", cfg['cur_max'])
        #self.setItById("Temmin", cfg['tem_min'])
        #self.setItById("Temmax", cfg['tem_max'])

        #self.setItById("Hummin", cfg['hum_min'])
        #self.setItById("Hummax", cfg['hum_max'])
        #self.setItById("min", cfg['output_min'])
        #self.setItById("xmin", cfg['output_crmin'])
        #self.setItById("xmax", cfg['output_crmax'])
        #self.setItById("max", cfg['output_max'])
        
        #var limit1 = document.getElementById(\"Tvmin\").value;var limit2 = document.getElementById(\"Tvmax\").value;var limit3 = document.getElementById(\"Tcmin\").value*10;var limit4 = document.getElementById(\"Tcmax\").value*10;var limit5 = document.getElementById(\"Temmin\").value;var limit6 = document.getElementById(\"Temmax\").value;var limit7 = document.getElementById(\"Hummin\").value;var limit8 = document.getElementById(\"Hummax\").value;var limit9 = document.getElementById(\"min\").value*10;var limit10 = document.getElementById(\"xmin\").value*10;var limit11 = document.getElementById(\"xmax\").value*10;var limit12 = document.getElementById(\"max\").value*10;var limit13 = document.getElementById(\"Tcxmin\").value*10;var limit14 = document.getElementById(\"Tcxmax\").value*10;
        
        jsSheet = 'var claerlimit = createXmlRequest();claerlimit.onreadystatechange = setdatlimit;ajaxget(claerlimit, \"/alllimit?a=\" +{limit1}+\"&b=\"+{limit2} +\"&c=\"+{limit3} + \"&d=\"+{limit4}+\"&e=\"+{limit5} +\"&f=\"+{limit6} + \"&g=\"+{limit7}+\"&h=\"+{limit8} +\"&i=\"+{limit9} + \"&j=\"+{limit10}+\"&k=\"+{limit11} + \"&l=\"+{limit12} +\"&m=\"+{limit13} + \"&n=\"+{limit14} +\"&\");'.format( limit1 = cfg['vol_min'] , limit2 = cfg['vol_max'] , limit3 = int(cfg['cur_min'])*10 , limit4 = int(cfg['cur_max'])*10 ,limit5 = cfg['tem_min'] , limit6 = cfg['tem_max'],limit7 = cfg['hum_min'] , limit8 = cfg['hum_max'] ,limit9 = int(cfg['output_min'])*10 , limit10 = int(cfg['output_crmin'])*10 , limit11 = int(cfg['output_crmax'])*10 , limit12 = int(cfg['output_max'])*10 , limit13 = int(cfg['cur_crmin'])*10 , limit14 = int(cfg['cur_crmax'])*10)
        #print(jsSheet)
        self.execJs(jsSheet)
        time.sleep(1)
        
    def checkCorrectHtml(self):
        cfg = self.cfgs
        self.check( 'LineN' , cfg['lines'] , '相数')
        self.check( 'CircuitN' , cfg['loops'] , '回路')
        self.check( 'OutputN' , cfg['outputs'] , '输出位' )
        self.check( 'neutral' , cfg['standar'] , '标准/中性')
        self.check( 'type' , cfg['series'] , '系列')
        self.check( 'language' , cfg['language'] , '中英文')
        self.check( 'breaker' , cfg['breaker'] , '断路器')
        self.check( 'serial' , cfg['modbus'] , 'IN/OUT级联方式')
        self.checkStr( 'mac1' , cfg['mac'] , 'mac地址')
        self.check( 'Tvmin' , cfg['vol_min'] , '总电压最小值')
        self.check( 'Tvmax' , cfg['vol_max'] , '总电压最大值')
        self.check( 'Tcmin' , cfg['cur_min'] , '总电流最小值')
        self.check( 'Tcxmin' , cfg['cur_crmin'] , '总电流下临界值')
        self.check( 'Tcxmax' , cfg['cur_crmax'] , '总电流上临界值' )
        self.check( 'Tcmax' , cfg['cur_max'] , '总电流最大值')

        self.check( 'Temmin' , cfg['tem_min'] , '温度最小值')
        self.check( 'Temmax' , cfg['tem_max'] , '温度最大值')
        self.check( 'Hummin' , cfg['hum_min'] , '湿度最小值')
        self.check( 'Hummax' , cfg['hum_max'] , '湿度最大值')
        self.check( 'min' , cfg['output_min'] , '输出位电流最小值')
        self.check( 'xmin' , cfg['output_crmin'] , '输出位电流下临界值')
        self.check( 'xmax' , cfg['output_crmax'] , '输出位电流上临界值')
        self.check( 'max' , cfg['output_max'] , '输出位电流最大值')
        self.driver.back()
        
        
        
    def checkTitleBar2(self):
        cfg = self.cfgs
        self.divClick(2)
        time.sleep(1)
        self.driver.find_element_by_id("titlebar2").click()
        time.sleep(1)
        
        line , loop = 1 , cfg['loops']
        list=[]
        cfgStr = []
        outputStr = []
        if( cfg['lines'] == 1 and cfg['loops'] == 1 ):
            line = 1
        else:
            line = 3
        for i in range(1 , line+1):
            list.append('Tcmin{0}'.format(i))
            list.append('Txcmin{0}'.format(i))
            list.append('Txcmax{0}'.format(i))
            list.append('Tcmax{0}'.format(i))
            cfgStr.append('cur_min')
            cfgStr.append('cur_crmin')
            cfgStr.append('cur_crmax')
            cfgStr.append('cur_max')
            if( loop != 2 ):
                outputStr.append('L{0}总电流最小值'.format(i))
                outputStr.append('L{0}总电流下临界值'.format(i))
                outputStr.append('L{0}总电流上临界值'.format(i))
                outputStr.append('L{0}总电流最大值'.format(i))
            else:
                if( i != 1 ):
                    outputStr.append('L{0}总电流最小值'.format(i))
                    outputStr.append('L{0}总电流下临界值'.format(i))
                    outputStr.append('L{0}总电流上临界值'.format(i))
                    outputStr.append('L{0}总电流最大值'.format(i))
                else:
                    outputStr.append('C{0}总电流最小值'.format(i-1))
                    outputStr.append('C{0}总电流下临界值'.format(i-1))
                    outputStr.append('C{0}总电流上临界值'.format(i-1))
                    outputStr.append('C{0}总电流最大值'.format(i-1))
        for i in range(1 , line+1):
            list.append('Tvmin{0}'.format(i))
            list.append('Tvmax{0}'.format(i))
            cfgStr.append('vol_min')
            cfgStr.append('vol_max')
            outputStr.append('L{0}总电压最小值'.format(i))
            outputStr.append('L{0}总电压最大值'.format(i))
        for i in range(1 , 2+1):
            list.append('Temmin{0}'.format(i))
            list.append('Temmax{0}'.format(i))
            cfgStr.append('tem_min')
            cfgStr.append('tem_max')
            outputStr.append('温度{0}最小值'.format(i))
            outputStr.append('温度{0}最大值'.format(i))
        for i in range(1 , 2+1):
            list.append('Hummin{0}'.format(i))
            list.append('Hummax{0}'.format(i))
            cfgStr.append('hum_min')
            cfgStr.append('hum_max')
            outputStr.append('湿度{0}最小值'.format(i))
            outputStr.append('湿度{0}最大值'.format(i))
        zz = zip(list , cfgStr , outputStr)
        for x,y,z in zz:
            #print(x)
            #Tvmin = self.driver.find_element_by_id(x).get_attribute('value')
            self.checkStr( x , cfg[y] , z)
            
    def checkTitleBar3(self):
        cfg = self.cfgs
        self.divClick(2)
        time.sleep(1)
        self.driver.find_element_by_id("titlebar3").click()
        time.sleep(1)
        
        op = cfg['outputs']
        list=[]
        cfgStr = []
        outputStr = []
       
        for i in range(1 , int(op)+1):
            list.append('min{0}'.format(i))
            list.append('xmin{0}'.format(i))
            list.append('xmax{0}'.format(i))
            list.append('max{0}'.format(i))
            cfgStr.append('output_min')
            cfgStr.append('output_crmin')
            cfgStr.append('output_crmax')
            cfgStr.append('output_max')
            outputStr.append('输出位{0}电流最小值'.format(i))
            outputStr.append('输出位{0}电流下临界值'.format(i))
            outputStr.append('输出位{0}电流上临界值'.format(i))
            outputStr.append('输出位{0}电流最大值'.format(i))
            
        zz = zip(list , cfgStr , outputStr)
        for x,y,z in zz:
            self.checkStr( x , cfg[y] , z)
            
        try:
            message =''
            self.driver.find_element_by_id('totalms')
        except NoSuchElementException:
            message =  '网页上找不到{0}ID;'.format('延时上电')
            self.sock.sendto(message.encode('gbk') , (self.ip , self.port))
            return
        self.setItById("totalms", cfg['delay_time'])
        jsSheet = 'var ms = parseFloat(document.getElementById(\"totalms\").value);var xmlset = createXmlRequest();xmlset.onreadystatechange = setdata;ajaxget(xmlset, \"/settime?a=\" + ms + \"&\");'
        #print(jsSheet)
        self.execJs(jsSheet)
        time.sleep(1)