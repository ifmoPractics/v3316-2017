using System;
using System.Collections.Generic;

using System.Text;
using System.Threading.Tasks;
using System.Linq;
using System.Windows.Media;

namespace Metro
{
    //class SecondPar
    //{
    //    public MetroNode Node { get; set; }
    //    public int Weight { get; set; }
    //}

    class Search
    {
        //public MetroNode Head { get; set; }
        //public SecondPar Tail { get; set; }
        public Dictionary<MetroNode, Dictionary<MetroNode, int>> edges = new Dictionary<MetroNode, Dictionary<MetroNode, int>>();
        private MetroNode Start { get; set; }
        private MetroNode End { get; set; }

        //Добавление ребра в список ребер
        public void AddEdge(MetroNode start, MetroNode end, int weight)
        {
            if (edges.ContainsKey(start))
            {
                edges[start].Add(end, weight);
            }
            else
            {
                Dictionary<MetroNode, int> sec = new Dictionary<MetroNode, int>();
                sec[end] = weight;
                edges[start] = sec;
            }
        }

        //Поиск кратчайшего пути по расстоянию
        public List<MetroNode> SearchMinByDistance(MetroNode start, MetroNode end)
        {
            Start = start;
            End = end;

            //Обнуляем цену для каждого узла
            Dictionary<MetroNode, Dictionary<MetroNode, int>>.ValueCollection val = edges.Values;
            foreach (Dictionary<MetroNode, int> elem in val)
            {
                Dictionary<MetroNode, int>.KeyCollection k = elem.Keys;
                foreach (MetroNode node in k)
                {
                    node.Cost = Int32.MaxValue;
                    node.Visited = false;
                    node.Parent = null;
                }
            }

            Start.Cost = 0;
            MetroNode currentNode = Start;
            GoingToNode2(currentNode,edges);
            currentNode = End;
            List<MetroNode> nodes = new List<MetroNode>();
            while (currentNode != Start)
            {
                nodes.Add(currentNode);
                currentNode = currentNode.Parent;
            }
            nodes.Add(start);

            return nodes;
        }



        //Поиск кратчайшего пути по переходам
        public List<MetroNode> SearchMinByOvertures(MetroNode start, MetroNode end)
        {
            Start = start;
            End = end;

            //Обнуляем цену для каждого узла
            Dictionary<MetroNode, Dictionary<MetroNode, int>>.ValueCollection val = edges.Values;
            foreach (Dictionary<MetroNode, int> elem in val)
            {
                Dictionary<MetroNode, int>.KeyCollection k = elem.Keys;
                foreach (MetroNode node in k)
                {
                    node.Cost = Int32.MaxValue;
                    node.Visited = false;
                    node.Parent = null;
                }
            }

            Dictionary<MetroNode, Dictionary<MetroNode, int>> edgesTemp = new Dictionary<MetroNode, Dictionary<MetroNode, int>>();
            foreach(KeyValuePair < MetroNode, Dictionary < MetroNode, int>> n in edges)
            {
                foreach(KeyValuePair<MetroNode, int> vn in n.Value)
                {
                    int weight = 0;
                    if(vn.Key.NodeColor != n.Key.NodeColor)
                    {
                        weight = 1;
                    }
                    else
                    {
                        weight = 0;
                    }

                    if (edgesTemp.ContainsKey(n.Key))
                    {
                        edgesTemp[n.Key].Add(vn.Key, weight);
                    }
                    else
                    {
                        Dictionary<MetroNode, int> sec = new Dictionary<MetroNode, int>();
                        sec[vn.Key] = weight;
                        edgesTemp[n.Key] = sec;
                    }
                }
            }

            Start.Cost = 0;
            MetroNode currentNode = Start;
            GoingToNode2(currentNode, edgesTemp);
            currentNode = End;
            List<MetroNode> nodes = new List<MetroNode>();
            while (currentNode != Start)
            {
                nodes.Add(currentNode);
                currentNode = currentNode.Parent;
            }
            nodes.Add(start);

            return nodes;
        }


        //Удаление элеманта
        public void DeleteElem(MetroNode n1, MetroNode n2)
        {
            edges[n1].Remove(n2);
        }

        //Существует ли связь
        public bool IsExist(MetroNode n1, MetroNode n2)
        {
            if (edges.ContainsKey(n1))
                if (edges[n1].ContainsKey(n2))
                    return true;
            return false;
        }

        //Проход по всем узлам
        private void GoingToNode2(MetroNode node, Dictionary<MetroNode, Dictionary<MetroNode, int>> dict)
        {
            Queue<MetroNode> queue = new Queue<MetroNode>();
            queue.Enqueue(node);
            node.Visited = true;

            while(queue.Count > 0)
            {
                MetroNode tmp = queue.Dequeue();
                Dictionary<MetroNode, int> elem = dict[tmp];

                foreach (KeyValuePair<MetroNode, int> n in elem)
                {
                    if ((n.Value + tmp.Cost) < n.Key.Cost)
                    {
                        n.Key.Cost = (n.Value + tmp.Cost);
                        n.Key.Parent = tmp;
                    }
                    if (!n.Key.Visited)
                    {
                        queue.Enqueue(n.Key);
                        n.Key.Visited = true;
                    }
                }
            }
        }
    }
}

