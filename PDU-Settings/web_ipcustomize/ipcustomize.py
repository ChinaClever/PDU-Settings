from ctrlset_ipcustomize.ipcustomize_web import  *

class IpCustomize(IpCustomizeWeb):

    def start_fun(self):
        ret = self.login()
        if(ret==False):
            self.driver.quit()
        else:
            self.setCorrect()
            self.driver.quit()

    def setTime(self):
        self.divClick(8)
        self.execJsAlert("check_time()")
        self.sendtoMainapp("设置设备时间", 1)

    def clearLogs(self):
        en = self.cfgs['log_en']
        if(int(en) < 1):
            return
        self.setTime()
        self.divClick(9)
        jsSheet = "xmlset = createXmlRequest();xmlset.onreadystatechange = setdata;ajaxgets(xmlset, \"/setlclear?a=\" + {0} + \"&\");"
        for num in range(0, 2):
            self.setSelect("loglist", num)
            self.execJs(jsSheet.format(num))
            time.sleep(1)
        self.sendtoMainapp("设备日志清除成功", 1)

    def setCorrect(self):
        cfg = self.cfgs
        ip = cfg['ip_prefix'] + cfg['ip_addr'] + cfg['backendaddress']
        self.driver.get(ip)
        time.sleep(1)
        self.driver.switch_to.default_content()

        self.setMacAddr()
        self.alertClick(cfg['setmaccontrolid'])
        self.sendtoMainapp("设备后台网页配置成功", 1)
        self.driver.back()
        time.sleep(0.5)
        
    def setMacAddr(self):
        cfg = self.cfgs
        try:   
            it = self.driver.find_element_by_id(cfg['maccontrolid'])
            mac = it.get_attribute('value')
            if "2C:26:5F:" in mac:
                self.sendtoMainapp('MAC-1',1)
            else:
                self.setItById(cfg['maccontrolid'], cfg['mac'], 'Mac地址')
        except:
            self.sendtoMainapp('控件ID错误',0)

    





