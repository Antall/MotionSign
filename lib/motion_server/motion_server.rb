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

post '/occupied/:room' do
  occupied = ( request.body.read&.to_i == 1)
  str = occupied ? "OCCUPIED" : "EMPTY"
  puts str
  str
end
