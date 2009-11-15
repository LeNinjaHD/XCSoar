#include "TaskBestMc.hpp"
#include <math.h>
#include "Util/Tolerances.hpp"
#include <algorithm>

TaskBestMc::TaskBestMc(const std::vector<OrderedTaskPoint*>& tps,
                       const unsigned activeTaskPoint,
                       const AIRCRAFT_STATE &_aircraft,
                       const GlidePolar &_gp,
                       const double _mc_min):
  ZeroFinder(_mc_min,10.0,TOLERANCE_BEST_MC),
  tm(tps,activeTaskPoint,_gp),
  aircraft(_aircraft) 
{
}

TaskBestMc::TaskBestMc(TaskPoint* tp,
                       const AIRCRAFT_STATE &_aircraft,
                       const GlidePolar &_gp):
  ZeroFinder(0.1,10.0,TOLERANCE_BEST_MC),
  tm(tp,_gp),
  aircraft(_aircraft) 
{
}

double TaskBestMc::f(const double mc) 
{
  tm.set_mc(std::max(0.001,mc));
  res = tm.glide_solution(aircraft);

  if (res.Vector.Distance>0) {
    return res.AltitudeDifference/res.Vector.Distance;
  } else {
    return res.AltitudeDifference;
  }
}

bool TaskBestMc::valid(const double mc) 
{
  double ff = f(mc);
  return (res.Solution== GlideResult::RESULT_OK) && (ff>=-tolerance*2.0);
}

double TaskBestMc::search(const double mc) 
{
  double a = find_zero(mc);
  if (!valid(a)) {
    return mc;
  } 
  return a;
}
