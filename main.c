#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct GraphNodeStr GraphNode;

struct GraphNodeStr {
    int id;
    bool visited;
    float minDistance;
};

typedef struct {
    float weight;
    GraphNode* a;
    GraphNode* b;
} GraphConnection;

typedef struct {
    GraphConnection* connections;
    GraphNode* nodes;
    int n;
} Graph;


void inputGraph(Graph* graph);

//actually that's Dijkstra’s Algorithm
float calculateDistanceTo(Graph graph, int nodeId);

GraphConnection* getAllConnectionsWithNode(GraphConnection* connections, GraphNode node, int n);

/*Data for testing
4
2
3
2
-1
4
2
3
 * result: 2
 */

int main() {

    Graph* graph = calloc(1, sizeof(Graph));
    inputGraph(graph);

    graph->nodes[0].minDistance = 0;

    int graphNodeToSearch;
    printf("graph node to search:");
    scanf("%d", &graphNodeToSearch);

    printf("distance %f", calculateDistanceTo(*graph, graphNodeToSearch));

    return 0;
}

void inputGraph(Graph* graph)
{
    printf("num of nodes:");
    scanf("%d", &graph->n);

    graph->nodes = calloc(graph->n, sizeof(GraphNode));
    for (int i=0; i < graph->n; i++)
    {
        graph->nodes[i].id = i;
        graph->nodes[i].visited = false;
        graph->nodes[i].minDistance = -1;
    }

    graph->connections = calloc(graph->n*graph->n, sizeof(GraphConnection));
    float weight;
    int k = 0;
    printf("Input connections(-1 no connection):\n");
    for (int i=0; i < graph->n; i++)
    {
        for (int j=i+1;j < graph->n; j++)
        {
            printf("input weight of connection between %d-%d: ", i, j);
            scanf("%f", &weight);

            if (weight != -1 )
            {
                graph->connections[k].a = &graph->nodes[i];
                graph->connections[k].b = &graph->nodes[j];
                graph->connections[k].weight = weight;
                k++;
            }
        }
    }
}

GraphConnection* getAllConnectionsWithNode(GraphConnection* connections, GraphNode node, int n)
{
    GraphConnection* res = calloc(n, sizeof(GraphConnection));
    int j = 0;
    for (int i=0; i< n*n; i++)
    {
        if (connections[i].a == NULL || connections[i].b == NULL)
            return res;

        if (connections[i].a->id == node.id || connections[i].b->id == node.id)
        {
            res[j] = connections[i];
            j++;
        }
    }


    return res;
}

float calculateDistanceTo(Graph graph, int nodeId)
{
    for (int i=0; i < graph.n; i++)
    {
        float dist = i == 0 ? (float) 0 : graph.nodes[i].minDistance, tDistance;

        GraphConnection* connectionsWithNode = getAllConnectionsWithNode(graph.connections, graph.nodes[i], graph.n);
        int j = 0;
        while (connectionsWithNode[j].a != NULL && connectionsWithNode[j].b != NULL)
        {
            if (connectionsWithNode[j].a->visited || connectionsWithNode[j].b->visited)
                goto end;


            if (connectionsWithNode[j].a->id == graph.nodes[i].id)
            {
                tDistance = dist + connectionsWithNode[j].weight;
                if (connectionsWithNode[j].b->minDistance == -1 || tDistance < connectionsWithNode[j].b->minDistance)
                    connectionsWithNode[j].b->minDistance = tDistance;
            }
            else
            {
                tDistance = dist + connectionsWithNode[j].weight;
                if (connectionsWithNode[j].a->minDistance == -1 || tDistance < connectionsWithNode[j].a->minDistance)
                    connectionsWithNode[j].a->minDistance = tDistance;
            }

            end:
            j++;
        }

        graph.nodes[i].visited = true;
    }

    return graph.nodes[nodeId].minDistance;
}