#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node {
    string vertex;
    int time;
    Node* next;

    Node(const string& v, int t) : vertex(v), time(t), next(nullptr) {}
};

class AdjacencyGraph {
private:
    vector<vector<int>> adjMatrix; // Adjacency matrix
    vector<string> vertices; // List of vertex names
    vector<Node*> adjList; // Adjacency list
    int numVertices; // Number of vertices

    // Method to create an adjacency list from the adjacency matrix
    void createAdjList() {
        adjList.resize(numVertices, nullptr);
        for (int i = 0; i < numVertices; i++) {
            adjList[i] = new Node(vertices[i], 0); // Initialize head node
            Node* current = adjList[i];

            for (int j = 0; j < numVertices; j++) {
                if (adjMatrix[i][j] != 0) {
                    current->next = new Node(vertices[j], adjMatrix[i][j]);
                    current = current->next;
                }
            }
        }
    }

public:
    // Constructor
    AdjacencyGraph() : numVertices(0) {
        adjMatrix.resize(20, vector<int>(20, 0));
    }

    // Method to input the graph details
    void inputGraph() {
        cout << "Enter number of cities (max. 20): ";
        cin >> numVertices;
        vertices.resize(numVertices);

        cout << "Enter names of cities:\n";
        for (int i = 0; i < numVertices; i++) {
            cin >> vertices[i];
        }

        cout << "Input adjacency matrix details:\n";
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                char choice;
                cout << "Is there a path between " << vertices[i] << " and " << vertices[j] << " (y/n)? ";
                cin >> choice;
                
                if (choice == 'y' || choice == 'Y') {
                    cout << "Enter time required to travel from " << vertices[i] << " to " << vertices[j] << " (in minutes): ";
                    cin >> adjMatrix[i][j];
                } else {
                    adjMatrix[i][j] = 0;
                }
            }
        }

        createAdjList();
    }

    // Method to display the adjacency matrix
    void displayAdjMatrix() {
        cout << "Adjacency Matrix:\n";
        cout << "\t";

        for (const auto& vertex : vertices) {
            cout << vertex << "\t";
        }
        cout << "\n";

        for (int i = 0; i < numVertices; i++) {
            cout << vertices[i] << "\t";
            for (int j = 0; j < numVertices; j++) {
                cout << adjMatrix[i][j] << "\t";
            }
            cout << "\n";
        }
    }

    // Method to display the adjacency list
    void displayAdjList() {
        cout << "Adjacency List:\n";
        for (int i = 0; i < numVertices; i++) {
            Node* current = adjList[i];
            cout << current->vertex;
            current = current->next;

            while (current) {
                cout << " -> " << current->vertex << " (time: " << current->time << " min)";
                current = current->next;
            }
            cout << "\n";
        }
    }

    // Destructor to free allocated memory
    ~AdjacencyGraph() {
        for (int i = 0; i < numVertices; i++) {
            Node* current = adjList[i];
            while (current) {
                Node* temp = current->next;
                delete current;
                current = temp;
            }
        }
    }
};

int main() {
    AdjacencyGraph graph;
    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Enter graph\n";
        cout << "2. Display adjacency matrix for cities\n";
        cout << "3. Display adjacency list for cities\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                graph.inputGraph();
                break;
            case 2:
                graph.displayAdjMatrix();
                break;
            case 3:
                graph.displayAdjList();
                break;
            case 4:
                return 0;
            default:
                cout << "Unknown choice. Please try again.\n";
                break;
        }
    }
}
