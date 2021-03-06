require 'rake/builder'

ARCHITECTURE       = 'x86_64'
PROFILED           = ENV['PROFILED']
GTEST_FILTER       = ENV['GTEST_FILTER']
LIBRARY_PATHS      = (ENV['CPPAR_LIBRARYPATHS'] || '').split(',')

def running_tests
  tasks = Rake.application.top_level_tasks
  tasks.any? { |task| task =~ /^test(\W|$)/ }
end

raise "Supply a PG_USER for tests" if running_tests && ENV['PG_USER'].nil?

PG_USER = ENV['PG_USER']

task :default => 'build'

desc 'Print help information for this Rakefile'
task :help do
  puts <<-EOT
    Build for profiling:
      $ PROFILED=1 rake ...
    When running tests, set up postgresql:
    - arrange for password-less access (via .pg_pass)
    - pass the name of a user on the command line:
      $ PG_USER=foo rake test:run
      the user must have the necessary privileges to create databases
    Test only certain files:
      $ PG_USER=foo GTEST_FILTER=Foo* rake test:run
    (See https://code.google.com/p/googletest/wiki/AdvancedGuide#Running_a_Subset_of_the_Tests)
   EOT
end

namespace :configure do
  desc 'Remove configure and related files files to allow rebuild'

  task :clean do
    `rm -rf aclocal.m4 autom4te.cache configure configure.ac Makefile.am Makefile.in config.status config.h.in`
  end

  desc 'Rebuild configure and associated files'
  task :rebuild => [:clean, 'configure.ac', 'aclocal.m4', 'config.h.in', :autoconf, :automake]

  task :'configure.ac' do
    version = File.read('VERSION').chomp
    Rake::Task['autoconf'].execute(OpenStruct.new(:project_title => 'cpp-active-record', :version => version))
  end

  task :'aclocal.m4' do
    `aclocal`
  end

  task :'config.h.in' do
    `autoheader`
  end

  task :autoconf do
    `autoconf`
  end

  task :automake do
    `automake`
  end
end

name          = "#{ARCHITECTURE}"
name          += '_profiled'       if PROFILED

include_paths = ['include', 'include/postgresql', 'include/postgresql/server']

Rake::Builder.new do |builder|
  builder.target               = "libactive_record_#{name}.a"
  builder.architecture         = ARCHITECTURE
  builder.source_search_paths  = %w(src src/attribute src/connection src/row src/table)
  builder.installable_headers  = ['include/**/*.h']
  builder.objects_path         = "objects/#{name}"
  builder.include_paths        = include_paths
  builder.compilation_options  = ['-pg'] if PROFILED
  builder.library_paths        = LIBRARY_PATHS
end

TEST_NAME                = "#{name}_test"
TEST_SOURCE_SEARCH_PATHS = ['test']

test_target_parameters =
  if GTEST_FILTER
    ["--gtest_filter=#{GTEST_FILTER}"]
  else
    []
  end

Rake::Builder.new do |builder|
  builder.task_namespace       = :test
  builder.target               = "./active_record_#{TEST_NAME}"
  builder.architecture         = ARCHITECTURE
  builder.source_search_paths  = TEST_SOURCE_SEARCH_PATHS
  builder.installable_headers  = ['test']
  builder.objects_path         = "test/objects/#{TEST_NAME}"
  builder.include_paths        = include_paths + ['test']
  builder.linker_options       = ['-L.']
  builder.library_dependencies = ['gtest', "active_record_#{name}", 'pq', 'sqlite3', 'pthread']
  builder.library_paths        = LIBRARY_PATHS + ["."]
  builder.target_prerequisites = [:"rake:build"]
  builder.default_task         = :run
  builder.target_parameters    = test_target_parameters
end
