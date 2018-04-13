#motion_server.rb

require 'sinatra'
require 'sinatra/reloader'
require 'pry'

get '/' do
  'Hello World'
end

get '/reserved/:room' do
  room = params[:room]
  reserved = true
  puts "IS #{room} RESERVED? => #{reserved}"
  rtn = reserved ? "1" : "0"
  rtn
end

get '/display/:room' do
  room = params[:room]
#--------1---------2---------3---------4
rtn = <<-RESPONSE
DATA
Sing us a song, you're the piano man
Sing us a song tonight
Well, we're all in the mood for a melody
And you've got us feelin' alright
RESPONSE
rtn
end

post '/occupied/:room' do
  occupied = ( request.body.read&.to_i == 1)
  str = occupied ? "OCCUPIED" : "EMPTY"
  puts str
  str
end
