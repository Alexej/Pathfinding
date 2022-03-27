#ifndef EF6440B7_CADB_4F91_835B_D74B462F1120
#define EF6440B7_CADB_4F91_835B_D74B462F1120

#include <vector>
#include "Binding.hpp"

namespace Pathfinding::Events
{
    class BindingsContainer
    {
        public:
            void addBinding(Binding binding)
            {
                bindings.push_back(binding);
            }

            void removeBindings(std::string_view bindingName);

            auto begin() const { return bindings.cbegin(); }
            
            auto end() const { return bindings.cend(); }
        
        private:
            std::vector<Binding> bindings;
    };
}

#endif /* EF6440B7_CADB_4F91_835B_D74B462F1120 */
