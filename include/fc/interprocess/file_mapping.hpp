#pragma once
#include <fc/fwd.hpp>
#include <fc/utility.hpp>

namespace boost {
  namespace interprocess {
    class file_mapping;
    class mapped_region;
  }
}
namespace fc {
  enum fm_mode_t {  //liruigang20180925 contract
    read_only,
    write_only,
    read_write
  };

  class file_mapping {
    public:
      file_mapping( const char* file, fm_mode_t );  //liruigang20180925 contract
      ~file_mapping();
    private:
      friend class mapped_region;
    #ifdef _WIN64
      fc::fwd<boost::interprocess::file_mapping,0x38> my;
    #else
      fc::fwd<boost::interprocess::file_mapping,0x24> my;
    #endif
  };

  class mapped_region {
    public:
      mapped_region( const file_mapping& fm, fm_mode_t m, uint64_t start, size_t size );   //liruigang20180925 contract
      mapped_region( const file_mapping& fm, fm_mode_t m );   //liruigang20180925 contract
      ~mapped_region();
      void  flush();
      void* get_address()const;
      size_t get_size()const;
    private:
      fc::fwd<boost::interprocess::mapped_region,40> my;
  };
}
