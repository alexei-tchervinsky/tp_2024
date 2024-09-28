std::vector<Polygon> readPolygonsFromFile(const std::string& filename) {
    std::vector<Polygon> polygons;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int vertexCount;
        Polygon polygon;

        iss >> vertexCount;
        polygon.points.resize(vertexCount);

        for (int i = 0; i < vertexCount; i++) {
            iss >> polygon.points[i].x >> polygon.points[i].y;
        }

        if (vertexCount == static_cast<int>(polygon.points.size())) {
            polygons.push_back(polygon);
        }
    }

    return polygons;
}
