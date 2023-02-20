# แลปเกี่ยวกับการสั่งบอร์ดด้วย Node-Red 


**อุปกรณ์ที่ใช้**: Raspberry pi 400 เครื่อง 02\
**SSID**: UMR-LAB_02\
**Password**: Ubon2565\
**user of rpi**: pi\
**password of rpi**: raspberry\
**IP raspberry pi**: 192.168.1.202\
**Gateway raspberry pi**: 192.168.1.1\
**DNS server**: 8.8.8.8

## แก้ไขข้อมูล Dashboard ของ Node-Red
1. เพิ่มปุ่ม output โยงมาหา ปุ่ม switch ตั้งชื่อ /forwardส่งค่าเป็น string "on" และ "off"
2. เพิ่มปุ่ม output โยงมาหา ปุ่ม switch ตั้งชื่อ /backward ส่งค่าเป็น string "on" และ "off"
3. เพิ่มปุ่ม output โยงมาหา ปุ่ม switch ตั้งชื่อ /left ส่งค่าเป็น string "on" และ "off"
4. เพิ่มปุ่ม output โยงมาหา ปุ่ม switch ตั้งชื่อ /right ส่งค่าเป็น string "on" และ "off"\
#หมายเหตุ: แต่ละอันต้อง เพิ่มเข้า group ก่อน ถ้ายังไม่มีให้สร้าง group (ถ้าไม่สร้างจะไม่แสดงในหน้า dashboard)\
#หมายเหตุ2: ทุกครั้งที่ทำเสร็จต้อง deploy ด้วย\
#หมายเหตุ3: สามารถแก้ไข ui ได้ด้วยการกดเลือกแก้ไขที่ group > layout

## ทดสอบ Node-Red Dashboard

```
http://192.168.1.202:1880/ui
```

## License
[MIT](https://choosealicense.com/licenses/mit/)
