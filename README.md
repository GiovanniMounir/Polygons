Donate through BTC: 1BUDZWput2E4G5DbN2Z3esYhNj7GRoyGHD

# Polygons
An application that parses and executes operations on polygons based on their vertices.

# Input Syntax
[(X1,Y1), (X2,Y2), ...; (M1,N1), (M2, N2), ...]
Where Xn,Yn are the coordinates of the vertices of Polygon1 and Mn,Yn are the coordinates of the vertices of Polygon2.

Example:
[(1,1),(4,1),(4,5),(1,5);(3,4),(6,4),(6,12),(3,12)]

# Valid Operations

| Command  | Description |
| ------------- | ------------- |
|Number_Polygons | Print the number of polygons.|
|Total_Number_Points | Print the total number of points in all polygons.|
|Minimum_X| Print the minimum X value of all points. |
|Maximum_X| Print the maximum X value of all points. |
|Minimum_Y| Print the minimum Y value of all points. |
|Maximum_Y| Print the maximum Y value of all points. |
|Enclosing_Rectangle| Print the minimum Enclosing Rectangle that includes all polygons inside it. |
|Total_Redundant_Points| The number of Redundant points in all polygons |
|Quit| End program |
|Polygon_Points n| List all points of the nth polygon (neglecting redundant points); n starts from 1 (1 means the first polygon)  |
|Point_Polygons (X,Y)| List all polygons IDs (ID is 1 for the first polygon, 2 for the second polygon,...)  of polygons that have the point (2,1) in their points list  |
|List_Polygons_Points More n| List Polygons having more than n points excluding redundant points where n is an integer. |
|List_Polygons_Points Less n| List Polygons having less than n points excluding redundant points where n is an integer. |
|List_Polygons_Points Equal n| List Polygons having exactly n points excluding redundant points where n is an integer. |
|List_Points_Polygons More n| List all Points that are in the list of more than n polygons where n is an integer. |
|List_Points_Polygons Less n| List all Points that are in the list of less than n polygons where n is an integer. |
|List_Points_Polygons Equal n| List all Points that are in the list of less than n polygons where n is an integer. |
|Polygon_Perimeter n| Print the perimeter of the nth polygon. |
|List_Triangles| List all Polygon IDs of polygons that are triangles. |
|List_Rectangles| List all Polygon IDs of polygons that are rectangles. | 
|List_Trapezoid| List all Polygon IDs of polygons that are trapezoid. |
|Inside_Rectangle (X1,Y1),(X2,Y2),(X3,Y3),(X4,Y4)| List all Polygon IDs of polygons that are inside the given rectangle. |
|Inside_Circle (Xc,Yc),r| List all Polygon IDs of polygons that are inside the given Circle where (Xc,Yc) are center coordinates, and r is the radius of the circle. |
|Polygon_Area n| Print the polygon area of the nth polygon |
|Polygons_Area_Range minArea,maxArea| List all Polygon IDs of polygons that have area <= minArea and >=maxArea. |
|Polygons_Enclosing_Point (X,Y)| List all Polygon IDs of polygons that have the point (X,Y) inside it (or on its boundaries). |
|Is_Intersecting i,j| | Prints TRUE if ith polygon intersects the jth polygon |
|Intersecting_Group i,j,k| Print TRUE if the list of polygon are all intersecting with each other (each one is intersecting with all other polygons) |
|Largest_Intersecting_Pair| Print the two IDs of polygons that are intersecting and having the largest sum of area. |
|Largest_Rectangle_Inside n| Print the largest rectangle that can inside the nth polygon. |
|Largest_Circle_Inside n| Print the largest circle that can inside the nth polygon. |
|Is_Connected i,j| Print TRUE if ith polygon is connected to the jth polygon |
|Is_Connected_Group i,j,k| Print TRUE if all polygon in the list are connected. |
|Maximum_Intersecting_Group| List polygon IDs forming the largest set of polygons that are intersecting (any ID should intersect with All other IDs in the list) |
|Maximum_Connected_Group| List polygon IDs forming the largest set of polygons that are connected directly or indirectly (through another polygon) |

# Disclaimer
This project is no longer maintained and may not always yield correct results. Please [open an issue](https://github.com/GiovanniMounir/Polygons/issues/new) for bug reports or suggestions.
