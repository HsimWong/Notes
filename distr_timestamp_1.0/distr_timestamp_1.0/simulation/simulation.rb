require "Clock.rb"
require "VariableFrequencyClock.rb"
require "PhaseDetector.rb"
require "SyncClock.rb"

# Statistics printing ______________________________________________

def clear_stats
  $phase_sum = 0.0;
  $phase_count = 0;
  $error_sum = 0.0;
  $error_count = 0;
  $max_error = 0;
end

def print_stats_header
  puts "# min_rtt\tmax_rtt\tavg_skew\tavg_err\tmax_err"
end

def print_stats
  phase_avg = $phase_sum / $phase_count
  error_avg = $error_sum / $error_count
  puts "#{$phase_detector.min_rtt}\t#{$phase_detector.max_rtt}\t#{phase_avg}\t#{error_avg}\t#{$max_error}"
end

# Low-level simulation ______________________________________

$reference = Clock.new

def run_simulation(minutes)
  advance_interval = 100000;
  (minutes * 60).times {
    ($REFERENCE_FREQ / advance_interval).times {
      Clock.advance_all advance_interval
      # seconds = $reference.time.to_f / $REFERENCE_FREQ.to_f
      error = $sync.error_bound
      if not error.nil?
        phase = $reference.time - $sync.time
        $phase_sum += phase.abs;
        $error_sum += error.abs;
        $phase_count += 1
        $error_count += 1
        $max_error = error.abs if $max_error < error.abs
      end
    }
    $sync.update
  }
end

# High-level scenario _________________________________________________

print_stats_header

0.step(900,100) { |i|
  $reference = Clock.new
  local      = Clock.new
  local.drift = 0           # up to 200 usec, e.g.
  local.variability = 10
  $phase_detector = PhaseDetector.new($reference)
  $sync = SyncClock.new(local, $phase_detector)
  $phase_detector.min_rtt = i
  $phase_detector.max_rtt = i + 100
  #$phase_detector.failure_rate = 0.0   # probability of failure, 0 to 1

  clear_stats
  run_simulation(10000) # number of simulated minutes
  print_stats
}
