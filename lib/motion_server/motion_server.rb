#motion_server.rb

require 'sinatra'
require 'sinatra/reloader'
require 'pry'

get '/' do
  'Hello World'
end

get '/prod/MotionSign' do
  room = params[:room_id]
  reserved = params[:occupied]
  puts "IS #{room} RESERVED? => #{reserved}"

  if params[:method_name] == "display"
rtn = <<-RESPONSE
DATA
NOW: #{Time.now.strftime("%^a %l:%M:%S %p")}
12345678901234567890
NEXT:       #{Time.now.strftime("%l:%M %p")}
Ben's & Antall's su
RESPONSE
    return rtn.strip
  end

  reserved
end
