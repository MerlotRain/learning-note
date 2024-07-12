#pragma once

#include <stdio.h>
#include <queue>
#include <pthread.h>
#include <chrono>
#include <time.h>

struct box_point_type{
    float vertex_min[3];
    float vertex_max[3];
};

enum operation{
    add_point,
    add_box,
    delete_point,
    delete_box,
    downsample_delete,
    push_down,
};

enum delete_point_storage
{
    not_record,
    delete_points_rec,
    multi_thread_rec,
};


template<class PointType>
class kdTree
{
public:
    using PointVector = std::vector<PointType, Eigen::aligned_allocator<PointType>>;
    using Ptr = std::shared_ptr<kdTree<PointType>>;

    struct kdTree_node {
        PointType point;
        int division_axis;
        int tree_size = 1;
        int invalid_point_num = 0;
        int down_delete_num = 0;
        bool point_deleted = false;
        bool tree_deleted = false;
        bool point_downsample_deleted = false;
        bool tree_downsample_deleted = false;
        bool need_push_down_to_left = false;
        bool need_push_down_to_right = false;
        bool working_flag = false;
        pthread_mutex_t push_down_mutex_lock;
       float node_range_x[2], node_range_y[2], node_range_z[2];
        float radius_sq;
        kdTree_node *left_cnode = nullptr;
        kdTree_node *right_cnode = nullptr;
        kdTree_node *parent_node = nullptr;
        float alpha_del;
        float alpha_bal;
    };

    struct operation_logger_type
    {
        PointType point;
        box_point_type boxpoint;
        bool tree_deleted, tree_downsample_deleted;
        operation op;
    };

    struct pointTypeCMP
    {
        PointType point;
        float dist = 0.0;
        pointTypeCMP(PointType p = PointType(), float d = INFINITY)
        {
            this->point = p;
            this->dist = d;
        };
        bool operator<(const pointTypeCMP &a) const
        {
            if (fabs(dist - a.dist) < 1e-10)
                return point.x < a.point.x;
            else
                return dist < a.dist;
        }
    };

    class manual_heap
    {        
        int heap_size = 0;
        int cap = 0;
        pointTypeCMP *heap;
        public:
        manual_heap(int max_capacity = 100)
        {
            cap = max_capacity;
            heap = new pointTypeCMP[max_capacity];
            heap_size = 0;
        }
        ~manual_heap() {delete[] heap;}
        void pop()
        {
            if(heap_size == 0)
                return;
            heap[0] = heap[heap_size-1];
            heap_size--;
            move_down(0);
        }
        pointTypeCMP top()
        {
            return heap[0];
        }

        void push(const pointTypeCMP& point)
        {
            if(heap_size>=cap) return;
            heap[heap_size] = point;
            float_up(heap_size);
            heap_size++;
        }
        int size() const {return heap_size;}
        void clear() {heap_size = 0;}

        private:
        void move_down(int heap_index)
        {
                        int l = heap_index * 2 + 1;
            pointTypeCMP tmp = heap[heap_index];
            while (l < heap_size)
            {
                if (l + 1 < heap_size && heap[l] < heap[l + 1])
                    l++;
                if (tmp < heap[l])
                {
                    heap[heap_index] = heap[l];
                    heap_index = l;
                    l = heap_index * 2 + 1;
                }
                else
                    break;
            }
            heap[heap_index] = tmp;
        }

        void float_up(int heap_index)
        {
            int ancestor = (heap_index - 1) / 2;
            pointTypeCMP tmp = heap[heap_index];
            while (heap_index > 0)
            {
                if (heap[ancestor] < tmp)
                {
                    heap[heap_index] = heap[ancestor];
                    heap_index = ancestor;
                    ancestor = (heap_index - 1) / 2;
                }
                else
                    break;
            }
            heap[heap_index] = tmp;
            return;
        }
    };


    class manual_queue
    {

    };
        
};