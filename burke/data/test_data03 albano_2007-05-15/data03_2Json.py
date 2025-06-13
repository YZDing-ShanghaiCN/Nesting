import pandas as pd
import json

df = pd.read_excel('albano.xlsx', skiprows=4)
item_num = 8
output_json_path = 'test_data03.json'

## 从xlsx文件中提取坐标
polygons = []
for i in range(0, 16, 2):
    x_coords = df.iloc[i, 2:].dropna().values
    y_coords = df.iloc[i+1, 2:].dropna().values

    x_coords = [int(x) for x in x_coords if str(x).replace('.', '', 1).isdigit()]
    y_coords = [int(y) for y in y_coords if str(y).replace('.', '', 1).isdigit()]

    points = [[x, y] for x, y in zip(x_coords, y_coords)]
    polygons.append(points)

## 转化为json
json_item_data = []
for k in range(item_num):
    json_item_data.append({"ID": k + 1, "data": [polygons[k]]})

json_data = {"items": json_item_data}
with open(output_json_path, "w") as json_file:
    json.dump(json_data, json_file, indent=4)