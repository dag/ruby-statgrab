require 'rake/rdoctask'

Rake::RDocTask.new do |rd|
  rd.rdoc_files = ["statgrab.c"]
  rd.title = "Statgrab for Ruby API"
  rd.options << '--charset' << 'utf-8' <<
                '--inline-source' << '--line-numbers' <<
                '--webcvs' <<
                  'http://github.com/dag/ruby-statgrab/tree/master/%s'
end
