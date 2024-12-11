import paho.mqtt.subscribe as subscribe

msg = subscribe.simple("canalx", hostname="192.168.1.9")
print("%s"%(msg.payload))
