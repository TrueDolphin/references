class VectorMath {
    
    //this whole file was a dream.

    //:0
    float GetAngleBetweenVectors(vector v1, vector v2) {
        float dotProduct = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
        float lengthProduct = Math.Sqrt((v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2]) * (v2[0] * v2[0] + v2[1] * v2[1] + v2[2] * v2[2]));
        float angle = Math.Acos(dotProduct / lengthProduct);
        return angle;
    }

    //generated pathing
    TVectorArray GenerateWaypoints(vector startPoint, vector endPoint, float stepSize) {
        TVectorArray waypoints;
        vector direction = endPoint - startPoint;
        float distance = vector.Distance(startPoint, endPoint);
        direction.Normalize();
        int numSteps = distance / stepSize;
        for (int i = 1; i < numSteps; i++) {
            vector waypoint = startPoint + direction * (i * stepSize);
            waypoints.Insert(waypoint);
        }
        waypoints.Insert(endPoint);
        return waypoints;
    }

    //split pathing from point and generate new pathing
    TVectorArray GenerateSplitPath(TVectorArray originalPath, int numSplitPoints, int maxPathLength) {
        TVectorArray newPath = new TVectorArray;
        array<int> splitPoints = new array<int>;
        for (int i = 0; i < numSplitPoints; i++) {
            int splitIndex = Math.RandomInt(1, originalPath.Count() - 2);
            splitPoints.Insert(splitIndex);
        }
        splitPoints.Sort();
        for (int j = 0; j < splitPoints[0]; j++) {
            newPath.Insert(originalPath[j]);
        }
        for (int k = 0; k < splitPoints.Count(); k++) {
            if (k < splitPoints.Count() - 1) {
                TVectorArray splitPath = GenerateWaypoints(originalPath[splitPoints[k]], originalPath[splitPoints[k+1]], maxPathLength);
                for (int l = 1; l < splitPath.Count(); l++) {
                    newPath.Insert(splitPath[l]);
                }
            } else {
                for (int m = splitPoints[i]; m < originalPath.Count(); m++) {
                    newPath.Insert(originalPath[m]);
                }
            }
        }
        for (int n = splitPoints[0] + 1; n < newPath.Count(); n++) {
            originalPath.RemoveItem(newPath[n]);
        }
        return newPath;
    }


    // insane generation of pathing
    TVectorArray GenerateRandomPath(vector start, vector end, float minDistance, float maxDistance, int numWaypoints) {
        TVectorArray path;
        path.Resize(numWaypoints + 2);
        path[0] = start;
        path[numWaypoints + 1] = end;
        for (int i = 1; i <= numWaypoints; i++) {
            vector prev = path[i - 1];
            vector next = path[numWaypoints + 1];
            if (i > 1) {
                prev = path[i - 1] + "0 0 2";
            }
            if (i < numWaypoints) {
                float distance = Math.RandomFloatInclusive(minDistance, maxDistance);
                vector offset = ExpansionMath.GetRandomPointInRing(prev, 0, distance);
                next = next + offset;
            }
            path[i] = GetSurfacePathATL(prev[0], prev[2], next[0], next[2]);
        }
        return path;
    }

    vector GetSurfacePathATL(float x1, float z1, float x2, float z2) {
        TVectorArray path = new TVectorArray;

        vector start_pos = ExpansionStatic.GetSurfacePosition(x1, z1);
        vector end_pos = ExpansionStatic.GetSurfacePosition(x2, z2);
        path = GenerateWaypoints(start_pos, end_pos, 1);

        return path[1];
    }

}