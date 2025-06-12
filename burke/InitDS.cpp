#include <clipper2/clipper.offset.h>  
#include <clipper2/clipper.h>  
#include <nlohmann/json.hpp>  
#include <iostream>  
#include <vector>  
#include <string>  
#include <fstream>  
#include <algorithm>  

using namespace Clipper2Lib;  
using namespace std;  

using json = nlohmann::json;  

// 获取json，输入一个json文件的路径，返回一个多边形的集合
// 如果是原始图形的json数据，则n个多边形，对应的nfp有n(n+1)/2个
// 调用方式：对于多边形i和j，如果i≥j，则生产NFP_ij，表示i固定j环绕，下标为 i + j(61-j) / 2 - 31
vector<PathsD> ReadPolygonfromJson(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return {};
    }

    json j;
    file >> j;
    vector<PathsD> PolygonSetArray;

    // json文件下Items对应一个数组，数组的每个元素都是一个字典，坐标存储在这些字典的data键值对  
    for (const auto& entry : j["Items"])
    {
        // 将每个元素字典中的data键对应的值提取出来  
        const auto& data = entry.at("data");
        PathsD onePolygon;  // 一个多边形，由多个路径组成

        for (const auto& path : data)
        {
            // 对于path中的每个元素，都是一个点的坐标对  
            PathD singlePath;
            for (const auto& point : path)
            {
                if (point.size() == 2)
                    singlePath.emplace_back(point[0], point[1]);
            }

            if (!singlePath.empty())
                onePolygon.push_back(singlePath);
        }

        if (!onePolygon.empty())
            PolygonSetArray.push_back(onePolygon);
    }

    return PolygonSetArray;
}



int main()  
{  
    string filename = "C:\\Users\\dingyouzheng\\Desktop\\Burke\\data\\test_data01_json\\TA001.json";
    string nfpfilename = "C:\\Users\\dingyouzheng\\Desktop\\Burke\\data\\test_data01NFP_json\\TA001nfp.json";
	vector<PathsD> polygons = ReadPolygonfromJson(filename);

	// 显示第一个多边形的面积
	double size = Area(polygons[0]);
	cout << "Area of the first polygon: " << size << endl;
	// 显示多边形的数量
	cout << "polygons has " << polygons.size() << " polygons." << endl;
    return 0;
}