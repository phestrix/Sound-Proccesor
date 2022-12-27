#include "processor.hpp"

Processor::Processor(std::string config_file, std::string output_file, std::vector<std::string> input_files) : m_config_file(config_file), m_output_file(output_file), m_input_files(input_files) {}

void Processor::Convert() {
  ConfigParser config(m_config_file);

  ConverterVector pipeline = std::move(CreatePipeline(config));

  WAVReaderVector wav_reader_vector = std::move(OpenWAVReaders(GetFileLinks(pipeline)));

  WAVWriter wav_writer(m_output_file);

  SampleVector buf(m_input_files.size());
  while (UpdateSampleVector(wav_reader_vector, buf)) {
    SampleBuffer working_sample = buf[0];

    for (ConverterPtr& converter : pipeline) {
      converter->Process(working_sample, buf);
    }

    wav_writer.WriteSample(working_sample);
  }
}

bool Processor::UpdateSampleVector(WAVReaderVector& wav_reader_vector, SampleVector& buf) {
  if (!wav_reader_vector[0].ReadSample(buf[0])) {
    return false;
  } else {
    for (int i = 1; i < wav_reader_vector.size(); ++i) {
      wav_reader_vector[i].ReadSample(buf[i]);
    }
  }
  return true;
}

FileLinks Processor::GetFileLinks(const ConverterVector& pipeline) {
  FileLinks file_links;
  for (const ConverterPtr& converter : pipeline) {
    file_links.merge(converter->GetFileLinks());
  }
  return file_links;
}

WAVReaderVector Processor::OpenWAVReaders(const FileLinks& file_links) {
  WAVReaderVector wav_reader_vector(m_input_files.size());
  for (int i : file_links) {
    if (i >= m_input_files.size()) {
      throw std::invalid_argument("Link doesn't exist");
    }
    wav_reader_vector[i].Open(m_input_files[i]);
  }
  return wav_reader_vector;
}

ConverterVector Processor::CreatePipeline(ConfigParser& config) {
  ConverterVector pipeline;
  while (true) {
    ConverterCommand converter_command = config.GetConverterComand();
    if (converter_command.empty()) {
      break;
    }
    ConverterPtr converter_ptr = ConverterInterface::Create(converter_command);
    pipeline.push_back(std::move(converter_ptr));
  }

  return pipeline;
}