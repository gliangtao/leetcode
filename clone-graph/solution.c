/**
Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.


OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the
node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/
*/

/**
 * #define NEIGHBORS_MAX_SIZE 100
 * struct UndirectedGraphNode {
 *     int label;
 *     struct UndirectedGraphNode *neighbors[NEIGHBORS_MAX_SIZE];
 *     int neighborsCount;
 * };
 */
#define VISITED_FLAG    (1 << ((sizeof(int) * 8) - 1))
#define NOT_VISTED(p)   (!(p->neighborsCount & VISITED_FLAG))
#define SET_VISITED(p)  (p->neighborsCount |= VISITED_FLAG)
#define WAS_VISTED(p)   ((p->neighborsCount & VISITED_FLAG))
#define CLR_VISITED(p)  (p->neighborsCount &= ~VISITED_FLAG)
//NOT finished. Want to use "Glue Node" as temp nodes
struct UndirectedGraphNode *cloneGraph(struct UndirectedGraphNode *graph) {
    if (!graph) return NULL;
    struct UndirectedGraphNode* node, *p, *nn;
    int qsize = 1024 * 2;
    struct UndirectedGraphNode** q = (struct UndirectedGraphNode**)malloc(sizeof(struct UndirectedGraphNode*) * qsize);
    int
    int qh, qt, saved_qt, ncount;
    qh = 0;
    qt = 1;
    q[0] = graph;
    q[1] = (struct UndirectedGraphNode*)malloc(sizeof(struct UndirectedGraphNode));
    SET_VISITED(graph);

    while (qh != qt) {
        saved_qt = qt;
        while (qh != saved_qt) {
            node = q[qh++];
            nn = q[qh++];
            if (qh >= qsize) qh -= qsize;
            ncount = node->neighborsCount;
            for (i = 0; i < ncount; i++) {
                p = node->neighbors[i];
                if (!p) continue;
                if (WAS_VISITED(p)) {
                    nn->neighbors[i]
                }
                if (p && NOT_VISITED(p)) {
                    q[qt++] = p;
                    q[qt++] = nn->neighbors[i] = (struct UndirectedGraphNode*)malloc(sizeof(struct UndirectedGraphNode));
                    if (qt >= qsize) qt -= qsize;
                    SET_VISITED(p);
                }

            }
        }
    }

    return ret;
}
