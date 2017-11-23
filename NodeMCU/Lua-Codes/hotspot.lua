cfg={}
cfg.ssid="SSID_OF_HOTSPOT"
cfg.pwd="PASSWORD_OF_HOTSPOT"
cfg.auth=wifi.WPA_PSK


wifi.setmode(wifi.SOFTAP)
wifi.ap.config(cfg)

function hotspot()
    table=wifi.ap.getclient()
    if  table~= nil then
        for mac,ip in pairs(table) do
        print(mac,ip)
        end
    end
end

tmr.alarm(0, 1000, 1,hotspot)
	
