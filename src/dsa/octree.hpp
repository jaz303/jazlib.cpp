#ifndef JAZLIB_OCTREE_HPP
#define JAZLIB_OCTREE_HPP

// Template arguments:
// T: type of vector components (e.g. float, double)
// D: type of data associated with each point in the octree.
template <class T, class D>
class octree
{
public:
    
    struct pair {
        vec3<T>     point;
        D           data;
    };
    
    octree(T half_size_)
    :   origin(vec3<T>(0, 0, 0)),
        half_size(vec3<T>(half_size_, half_size_, half_size_)),
        node_type(LEAF),
        n_pairs(0)
    { }
    
    octree(vec3<T> origin_, T half_size_)
    :   origin(origin_),
        half_size(vec3<T>(half_size_, half_size_, half_size_)),
        node_type(LEAF),
        n_pairs(0)
    { }
    
    octree(vec3<T> origin_, vec3<T> half_size_)
    :   origin(origin_),
        half_size(half_size_),
        node_type(LEAF),
        n_pairs(0)
    { }
    
    ~octree() {
        if (node_type == PARENT) {
            for (int i = 0; i < 8; i++) {
                delete children[i];
            }
        } else {
            for (int i = 0; i < n_pairs; i++) {
                ((pair*)pairs)[i].~pair();
            }
        }
    }
    
    void insert(vec3<T> point, D data) {
        if (node_type == LEAF) {
            if (n_pairs < MAX_PAIRS) {
                ((pair*)pairs)[n_pairs].point = point;
                ((pair*)pairs)[n_pairs].data = data;
                n_pairs++;
            } else {
                node_type = PARENT;
                pair tmp_pair = ((pair*)pairs)[0];
                for (int i = 0; i < 8; i++) {
                    vec3<T> new_origin = origin;
                    vec3<T> new_half_size = half_size * 0.5;
                    new_origin.x += new_half_size.x * ((i & 4) ? 1 : -1);
                    new_origin.y += new_half_size.y * ((i & 2) ? 1 : -1);
                    new_origin.z += new_half_size.z * ((i & 1) ? 1 : -1);
                    children[i] = new octree(new_origin, new_half_size);
                }
                children[ix_for_point(tmp_pair.point)]->insert(tmp_pair.point, tmp_pair.data);
                children[ix_for_point(point)]->insert(point, data);
            }
        } else {
            children[ix_for_point(point)]->insert(point, data);
        }
    }
    
    void query(vec3<T> point, T radius) {
        
    }
    
private:
    
    static const int        MAX_PAIRS = 1;
    
    vec3<T>                 origin;
    vec3<T>                 half_size;
    enum { PARENT, LEAF }   node_type;
    
    union {
        octree<T,D>*        children[8];
        struct {
            int             n_pairs;
            char            pairs[sizeof(pair) * MAX_PAIRS];
        };
    };
    
    int ix_for_point(vec3<T> p) const {
        int ix = 0;
        if (p.x >= origin.x) ix |= 4;
        if (p.y >= origin.y) ix |= 2;
        if (p.z >= origin.z) ix |= 1;
        return ix;
    }
};

#endif