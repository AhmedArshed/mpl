#define BOOST_TEST_MODULE graph_communicator

#include <boost/test/included/unit_test.hpp>
#include <mpl/mpl.hpp>

bool graph_communicator_test() {
  const mpl::communicator &comm_world=mpl::environment::comm_world();
  int size=comm_world.size();
  mpl::graph_communicator::edge_set es;
  for (int i=1; i<size; ++i) {
    es.insert({ 0, i });
    es.insert({ i, 0 });
  }
  mpl::graph_communicator comm_g(comm_world, es);
  if (comm_g.neighbors_count(0)!=comm_g.size()-1)
    return false;
  auto nl0{ comm_g.neighbors(0) };
  if (nl0.size()!=comm_g.size()-1)
    return false;
  auto nl1{ comm_g.neighbors(1) };
  if (nl1.size()!=1)
    return false;
  return true;
}

BOOST_AUTO_TEST_CASE(graph_communicator) {
  BOOST_TEST(graph_communicator_test());
}
