import json
import os

def txt2json(txt_file_path, output_json_path):
    with open(txt_file_path, 'r') as file:
        lines = file.readlines()

    first_line = lines[0].strip().split()
    item_num = int(first_line[0])

    # 第二行：得到板子的尺寸和大小
    second_line = lines[1].strip().split()
    board_width, board_height = int(second_line[0]), int(second_line[1])

    # 从第三行开始获取零件坐标
    location_lists = []

    for i in range(item_num):
        current_line = lines[i + 2].strip().split()
        vertices_num = int(current_line[0])

        current_loaction = []
        for j in range(vertices_num):
            x = int(current_line[1 + j * 2])
            y = int(current_line[2 + j * 2])
            current_loaction.append([x, y])

        location_lists.append(current_loaction)

    # 生成JSON格式的数据
    json_item_data = []
    for k in range(item_num):
        json_item_data.append({"ID": k + 1, "data": [location_lists[k]]})

    json_data = {"Items": json_item_data}

    with open(output_json_path, "w") as json_file:
        json.dump(json_data, json_file, indent=4)

def process_folder(input_folder, output_folder):
    for filename in os.listdir(input_folder):
        if filename.endswith(".txt") and filename.startswith("T"):
            base_name = os.path.splitext(filename)[0]
            
            txt_file_path = os.path.join(input_folder, filename)
            json_file_path = os.path.join(output_folder, f"{base_name}.json")
            
            txt2json(txt_file_path, json_file_path)

if __name__ == "__main__":
    base_path = "data\\"
    
    for i in range(1, 3):
        input_folder = os.path.join(base_path, f"test_data{i:02}")
        output_folder = os.path.join(base_path, f"test_data{i:02}_json")

        process_folder(input_folder, output_folder)