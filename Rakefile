require 'rubygems'
require 'rake/rdoctask'
require 'rake/gempackagetask'

spec = eval(File.read("statgrab.gemspec"))

Rake::RDocTask.new do |rd|
  rd.rdoc_files = ["statgrab.c"]
  rd.options << spec.rdoc_options
  rd.options.flatten!
end

desc "Publish RDoc API documentation to Rubyforge"
task :publish_rdoc => :rdoc do
  sh "rsync -aCv html/ \
    dag@rubyforge.org:/var/www/gforge-projects/statgrab/doc/"
end

Rake::GemPackageTask.new(spec) do |pkg|
  pkg.need_tar_gz = true
  pkg.need_zip = true
end
