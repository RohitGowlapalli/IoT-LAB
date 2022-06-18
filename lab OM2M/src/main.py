from onem2m import *
uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"
ae = "HC-Sr04"
cnt = "node1"

create_ae(uri_cse,ae)
uri_ae = uri_cse +"/"+ ae
create_cnt(uri_ae, cnt)
uri_cnt = uri_ae + "/" + cnt
create_data_cin(uri_cnt,190)
