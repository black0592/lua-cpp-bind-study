
#include "SingleTweener.h"
#include <iostream>
#include <fstream>

using namespace Aurora;

class tester
{
public:
  void run ( std::ostream& output, double init, double end, double duration, SingleTweener::EasingFunction e );
  void run_ref ( std::ostream& output, double init, double end, double duration, SingleTweener::EasingFunction e );

  void set_val(double date) {m_val=date; std::cout<< m_date << '\t' << m_val << std::endl;}
  double get_val() const {return m_val;}

private:
  void print_val( double d ) const;

private:
  double m_date;
  double m_val;

  std::ostream* m_output;

}; // class tester

void tester::print_val( double d ) const
{
  *m_output << m_date << '\t' << d << std::endl;
} // print_val()

void tester::run( std::ostream& output, double init, double end, double duration, SingleTweener::EasingFunction e )
{
  SingleTweener t (init, end, duration, std::bind(&tester::set_val, this, std::placeholders::_1), e );

  m_output = &output;
  m_date = 0;
  m_val = 0;

  t.Update(0);

  while ( !t.IsFinished() )
    {
      m_date += 0.1;
      t.Update(0.1);
    }
} // run()

void tester::run_ref ( std::ostream& output, double init, double end, double duration, SingleTweener::EasingFunction e )
{
  double val(0);
  SingleTweener t(val, end, duration, e );

  m_output = NULL;
  m_date = 0;

  t.Update(0);

  while ( !t.IsFinished() )
    {
      m_date += 0.1;
      t.Update(0.1);
      output << m_date << '\t' << val << std::endl;
    }
} // run_ref()

template<typename Easing>
void test()
{
  tester t;

  t.run_ref( std::cout, 0, 1, 2, Easing::EaseIn );
  //t.run( std::cout, 0, 1, 2, Easing::EaseOut );
  //t.run( std::cout, 0, 1, 2, Easing::EaseInOut );
} // test()

int main( int argc, char* argv[] )
{

//  test<EaseNone>();
//   test<easing_back>();
//   test<easing_bounce>();
//   test<easing_circ>();
//   test<easing_cubic>();7
//   test<easing_elastic>();
//   test<easing_expo>();
   test<EasingLinear>();
//   test<easing_quad>();
//   test<easing_quart>();
//   test<easing_quint>();
//   test<easing_sine>();

  getchar();


  return 0;
}
