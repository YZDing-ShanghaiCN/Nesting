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

// ��ȡjson������һ��json�ļ���·��������һ������εļ���
// �����ԭʼͼ�ε�json���ݣ���n������Σ���Ӧ��nfp��n(n+1)/2��
// ���÷�ʽ�����ڶ����i��j�����i��j��������NFP_ij����ʾi�̶�j���ƣ��±�Ϊ i + j(61-j) / 2 - 31
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

    // json�ļ���Items��Ӧһ�����飬�����ÿ��Ԫ�ض���һ���ֵ䣬����洢����Щ�ֵ��data��ֵ��  
    for (const auto& entry : j["Items"])
    {
        // ��ÿ��Ԫ���ֵ��е�data����Ӧ��ֵ��ȡ����  
        const auto& data = entry.at("data");
        PathsD onePolygon;  // һ������Σ��ɶ��·�����

        for (const auto& path : data)
        {
            // ����path�е�ÿ��Ԫ�أ�����һ����������  
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

	// ��ʾ��һ������ε����
	double size = Area(polygons[0]);
	cout << "Area of the first polygon: " << size << endl;
	// ��ʾ����ε�����
	cout << "polygons has " << polygons.size() << " polygons." << endl;
    return 0;
}