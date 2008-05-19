Gem::Specification.new do |s|
  s.name = 'statgrab'
  s.version = '0.1'
  s.summary = 'Ruby bindings to libstatgrab portable system statistics library'
  s.files = ['statgrab.c', 'README.mkdn', 'LICENSE']
  s.extensions << 'extconf.rb'
  s.has_rdoc = true
  s.extra_rdoc_files = ['statgrab.c']
  s.rdoc_options << '--charset' << 'utf-8' <<
                    '--inline-source' << '--line-numbers' <<
                    '--webcvs' <<
                      'http://github.com/dag/ruby-statgrab/tree/master/%s' <<
                    '--title' << 'Statgrab for Ruby API' <<
                    '--main' << 'Statgrab'
  s.author = 'Dag Odenhall'
  s.email = 'dag.odenhall@gmail.com'
  s.homepage = 'http://statgrab.rubyforge.org'
  s.rubyforge_project = 'statgrab'
end
