Gem::Specification.new do |s|
  s.name = 'statgrab'
  s.version = '0.1'
  s.summary = 'Ruby bindings to libstatgrab portable system statistics library'
  s.files = ['statgrab.c', 'LICENSE']
  s.extensions << 'extconf.rb'
  s.author = 'Dag Odenhall'
  s.email = 'dag.odenhall@gmail.com'
  s.homepage = 'http://statgrab.rubyforge.org'
  s.rubyforge_project = 'statgrab'
end
