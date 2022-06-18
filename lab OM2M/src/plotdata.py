from onem2m import *
import json
import matplotlib.pyplot as plt

content = []
creation_time = []

uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"
ae = "HC-Sr04"
cnt = "node1"

uri_ae = uri_cse + "/" + ae
uri_cnt = uri_ae + "/" + cnt
'''
headers = {
    'X-M2M-Origin': 'admin:admin',
    'Content-type': 'application/json'
}'''

response = get_data(uri_ae + "/node1?rcn=4")
print(response)


for data in response["m2m:cnt"]["m2m:cin"][-20:]:
    content.append(float(data["con"]))
    creation_time.append(data["ct"][-4:-2] + ":" + data["ct"][-2:])

print(content)
print(creation_time)
plt.plot(creation_time, content)
plt.show()


'''
while (len(content) < 10):
    response = requests.get(uri_cnt + "/la", headers=headers)
    y = json.loads(response.content)
    content.append(float(y['m2m:cin']['con']))
    creation_time.append(y['m2m:cin']['ct'])

print(content)
print(creation_time)'''