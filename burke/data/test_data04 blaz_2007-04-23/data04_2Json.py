import json

input_txt_path = "blaz.txt"
output_json_path = "test_data04.json"

with open(input_txt_path, 'r') as file:
    lines = file.readlines()

item_num = 7
last_num_line = 0
polygons = []

for i in range(item_num):
    num_line = int(lines[4 + last_num_line].strip().split()[0])
    
    polygon_i = []
    for j in range(0, num_line):
        line = lines[last_num_line + j + 6].strip().split()
        x, y = int(line[0]), int(line[1])
        polygon_i.append([x, y])
    
    polygons.append(polygon_i)
    last_num_line += (7 + num_line)

## 转化为json
json_item_data = []
for k in range(item_num):
    json_item_data.append({"ID": k + 1, "data": [polygons[k]]})

json_data = {"items": json_item_data}
with open(output_json_path, "w") as json_file:
    json.dump(json_data, json_file, indent=4)