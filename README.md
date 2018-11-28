# blogwriter
txt based minimalistic blog

compiling with gcc: gcc blog.c -o blog

usage and stuff
  before compilation you should edit the target, temp and rss vars in blog.c 
  once compiled and executed the program will ask your for a pseudonym, under which your blogarticle will be released.
  after that it will ask you for the text you want to publish. you can use html. hitting enter-key publishes your text.
  
  the rss feed will contain your full text. the rss feed will only publish your last 11 articles.
