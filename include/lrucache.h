#include <unordered_map>
#include <utility>
#include <memory>
namespace cache{ 
template <class key_t, class value_t>
class lru_node
{
public:
    typedef std::pair<key_t, value_t> kv_pair_t;
    kv_pair_t node_value;;
    std::shared_ptr<lru_node> next;
    std::shared_ptr<lru_node> last;
    lru_node(kv_pair_t& _v):
        node_value(_v), next(nullptr){}
    ~lru_node()=default;
};

template<class key_t, class value_t>
class lru_cache{
    private:
        typedef std::pair<key_t, value_t> kv_pair_t;
        typedef lru_node<key_t, value_t> node_t;
        typedef std::shared_ptr<node_t> node_ptr_t;

        node_ptr_t head;
        node_ptr_t tail;
        std::unordered_map<key_t, node_ptr_t> _cache;
        int _max_size;

    public:
        int _current_size;
        lru_cache(int max_size): _max_size(max_size), head(nullptr), tail(nullptr, _current_size(0)){}
        bool set(key_t k, value_t v){
            bool res;
            node_ptr_t n = std::make_shared<node_t>((std::make_pair(k, v)));
            _cache[k] = n;
            if(head == nullptr){
                head = n;
                tail = n;
            }else{
                n->next = head;
                head->last = n;
                head = n;
            }
            _current_size++;

            if(_current_size  == _max_size){
                res = _cache.erase(tail->value.first());
                tail = tail->last;
                tail->next = nullptr;
            }
            return res;
        }

        value_t get(key_t k){
            const auto it = _cache.find(k);
            if(it == _cache.cend()){
                throw std::range_error("No such key in cache");
            }
            const auto p = *it;
            const node_ptr_t last = p->last;
            last->next = p->next;
            p->next = head;
            p->last = p;
            p->last = nullptr;
            head = p;
            return std::move(p->value.second());
        }
        void clear(){
            head = nullptr;
            tail = nullptr;
            _current_size = 0;
            _cache.clear();
        }
        size_t size(){
            return _cache.size();
        }
};

}
